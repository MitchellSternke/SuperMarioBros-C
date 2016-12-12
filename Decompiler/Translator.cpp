#include <fstream>
#include <sstream>

#include "Translator.hpp"

void translateAst(AstRootNode* ast, const std::string& outputFilename)
{
    std::ofstream outputFile(outputFilename);

    outputFile << "#include \"Decompiled.hpp\"\n\n";

    // First, translate all constants
    outputFile << "// Constants\n";
    for( auto& n : ast->children )
    {
        if( n->type == AST_CONSTANT )
        {
            outputFile << n->translate(nullptr) << std::endl;
        }
    }
    outputFile << std::endl;

    // Classify labels
    std::list<AstLabelNode*> dataLabels;
    std::list<AstLabelNode*> codeLabels;
    for( auto& n : ast->children )
    {
        if( n->type == AST_LABEL )
        {
            AstLabelNode* l = static_cast<AstLabelNode*>(n);
            if( l->children.size() == 0 )
            {
                // Empty data label (right above another)
                dataLabels.push_back(l);
                continue;
            }
            auto& m = l->children.front();
            if( m->type == AST_DATA )
            {
                dataLabels.push_back(l);
            }
            else
            {
                codeLabels.push_back(l);
            }
        }
    }

    // Load data from data labels into the NES address space
    outputFile << "// Generated Data Addresses\n";
    int address = 0x8000;
    std::stringstream dataLoadCode;
    dataLoadCode << "void SMBEngine::loadConstantData()\n{\n";
    for( auto& l : dataLabels )
    {
        int bytes = 0;
        for( auto& m : l->children )
        {
            AstDataNode* d = static_cast<AstDataNode*>(m);
            bytes += d->data.size();
        }

        dataLabelNameHashes.insert(hash(l->name));

        // Create an alias for the address of the data
        char addressAsHex[16];
        sprintf(addressAsHex, "0x%x", address);
        outputFile << "#define " << l->name << " " << addressAsHex << std::endl;

        if (bytes > 0)
        {
            dataLoadCode << TAB << "writeData(" << l->name << ", " << l->name << "__data" << ", sizeof(" << l->name << "__data));\n";
        }

        address += bytes;
    }
    dataLoadCode << "}\n";
    outputFile << std::endl;

    // Transform data labels into constants
    outputFile << "// Constant data\n";
    for( auto& l : dataLabels )
    {
        if( l->children.empty() )
        {
            outputFile << "static const uint8_t* " << l->name << "__data = nullptr;\n";
            continue;
        }
        outputFile << "static const uint8_t " << l->name << "__data[] = {\n";
        bool firstLine = true;
        for( auto& m : l->children )
        {
            AstDataNode* d = static_cast<AstDataNode*>(m);
            if( d->bits == 16 )
            {
                continue;
            }

            if( !firstLine )
            {
                outputFile << ",\n";
            }
            firstLine = false;

            outputFile << TAB;
            bool firstItem = true;
            for( auto& dataItem : d->data )
            {
                if( !firstItem )
                {
                    outputFile << ", ";
                }
                firstItem = false;

                TranslationParams params;
                params.substituteNames = true;
                outputFile << dataItem->translate(&params);
            }
        }
        outputFile << "\n};\n\n";
    }

    // Output initialization code
    outputFile << dataLoadCode.str() << std::endl;

    // Translate code labels
    outputFile << "void SMBEngine::code(int mode)\n{\n" << TAB << "switch(mode)\n" << TAB << "{\n" << TAB << "case 0:\n" << TAB << TAB << "loadConstantData();\n" << TAB << TAB << "goto Start;\n" << TAB << "case 1:\n" << TAB << TAB << "goto NonMaskableInterrupt;\n" << TAB << "}\n";
    for( auto& l : codeLabels )
    {
        if( l->name.compare("JumpEngine") == 0 )
        {
            // We don't need to translate this since it is a special case that is no longer needed
            continue;
        }

        outputFile << l->name << ":\n";
        for( auto& m : l->children )
        {
            outputFile << m->translate(nullptr);
        }
    }

    // Generate a switch for return labels
    outputFile << "Return: // Return Handler\n" << TAB << "switch(popReturnIndex())\n" << TAB << "{\n";
    for( int i = 0; i < AstCodeNode::returnLabelIndex; i++ )
    {
        char indexStr[8];
        sprintf(indexStr, "%d", i);
        outputFile << std::string(TAB) + "case " + indexStr + ":\n" + TAB + TAB + "goto Return_" + indexStr + ";\n";
    }
    outputFile << TAB << "}\n";

    // Code is complete
    outputFile << "}\n";

    /*
    // Then, translate all data-only labels
    for( auto& n : ast->children )
    {
        if( n->type == AST_LABEL )
        {
            AstLabelNode* l = static_cast<AstLabelNode*>(n);
            int bits = 0;
            for( auto& m : l->children )
            {
                if( m->type != AST_DATA )
                {
                    goto continue_main_loop;
                }
                AstDataNode* d = static_cast<AstDataNode*>(m);
                if( bits != 0 && d->bits != bits )
                {
                    // Can't group this as a single node
                    std::cout << "Warning: can't translate data label \"" << l->name << "\"" << std::endl;
                    goto continue_main_loop;
                }
                bits = d->bits;
            }

            outputFile << "const " << (bits == 16 ? "uint16_t " : "uint8_t ") << l->name << " = [\n";
            bool firstLine = true;
            for( auto& m : l->children )
            {
                if( !firstLine )
                {
                    outputFile << ",\n";
                }
                firstLine = false;

                AstDataNode* d = static_cast<AstDataNode*>(m);
                outputFile << "\t";
                bool firstItem = true;
                for( auto& dataItem : d->data )
                {
                    if( !firstItem )
                    {
                        outputFile << ", ";
                    }
                    firstItem = false;
                    outputFile << dataItem->translate();
                }
            }
            outputFile << "\n];\n\n";
        }
continue_main_loop:;
    }
    */
}
