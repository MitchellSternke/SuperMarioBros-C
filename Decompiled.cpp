#include "Decompiled.hpp"
#include "Util.hpp"

// Constants
#define PPU_CTRL_REG1 0x2000
#define PPU_CTRL_REG2 0x2001
#define PPU_STATUS 0x2002
#define PPU_SPR_ADDR 0x2003
#define PPU_SPR_DATA 0x2004
#define PPU_SCROLL_REG 0x2005
#define PPU_ADDRESS 0x2006
#define PPU_DATA 0x2007
#define SND_REGISTER 0x4000
#define SND_SQUARE1_REG 0x4000
#define SND_SQUARE2_REG 0x4004
#define SND_TRIANGLE_REG 0x4008
#define SND_NOISE_REG 0x400c
#define SND_DELTA_REG 0x4010
#define SND_MASTERCTRL_REG 0x4015
#define SPR_DMA 0x4014
#define JOYPAD_PORT 0x4016
#define JOYPAD_PORT1 0x4016
#define JOYPAD_PORT2 0x4017
#define ObjectOffset 0x08
#define FrameCounter 0x09
#define SavedJoypadBits 0x06fc
#define SavedJoypad1Bits 0x06fc
#define SavedJoypad2Bits 0x06fd
#define JoypadBitMask 0x074a
#define JoypadOverride 0x0758
#define A_B_Buttons 0x0a
#define PreviousA_B_Buttons 0x0d
#define Up_Down_Buttons 0x0b
#define Left_Right_Buttons 0x0c
#define GameEngineSubroutine 0x0e
#define Mirror_PPU_CTRL_REG1 0x0778
#define Mirror_PPU_CTRL_REG2 0x0779
#define OperMode 0x0770
#define OperMode_Task 0x0772
#define ScreenRoutineTask 0x073c
#define GamePauseStatus 0x0776
#define GamePauseTimer 0x0777
#define DemoAction 0x0717
#define DemoActionTimer 0x0718
#define TimerControl 0x0747
#define IntervalTimerControl 0x077f
#define Timers 0x0780
#define SelectTimer 0x0780
#define PlayerAnimTimer 0x0781
#define JumpSwimTimer 0x0782
#define RunningTimer 0x0783
#define BlockBounceTimer 0x0784
#define SideCollisionTimer 0x0785
#define JumpspringTimer 0x0786
#define GameTimerCtrlTimer 0x0787
#define ClimbSideTimer 0x0789
#define EnemyFrameTimer 0x078a
#define FrenzyEnemyTimer 0x078f
#define BowserFireBreathTimer 0x0790
#define StompTimer 0x0791
#define AirBubbleTimer 0x0792
#define ScrollIntervalTimer 0x0795
#define EnemyIntervalTimer 0x0796
#define BrickCoinTimer 0x079d
#define InjuryTimer 0x079e
#define StarInvincibleTimer 0x079f
#define ScreenTimer 0x07a0
#define WorldEndTimer 0x07a1
#define DemoTimer 0x07a2
#define Sprite_Data 0x0200
#define Sprite_Y_Position 0x0200
#define Sprite_Tilenumber 0x0201
#define Sprite_Attributes 0x0202
#define Sprite_X_Position 0x0203
#define ScreenEdge_PageLoc 0x071a
#define ScreenEdge_X_Pos 0x071c
#define ScreenLeft_PageLoc 0x071a
#define ScreenRight_PageLoc 0x071b
#define ScreenLeft_X_Pos 0x071c
#define ScreenRight_X_Pos 0x071d
#define PlayerFacingDir 0x33
#define DestinationPageLoc 0x34
#define VictoryWalkControl 0x35
#define ScrollFractional 0x0768
#define PrimaryMsgCounter 0x0719
#define SecondaryMsgCounter 0x0749
#define HorizontalScroll 0x073f
#define VerticalScroll 0x0740
#define ScrollLock 0x0723
#define ScrollThirtyTwo 0x073d
#define Player_X_Scroll 0x06ff
#define Player_Pos_ForScroll 0x0755
#define ScrollAmount 0x0775
#define AreaData 0xe7
#define AreaDataLow 0xe7
#define AreaDataHigh 0xe8
#define EnemyData 0xe9
#define EnemyDataLow 0xe9
#define EnemyDataHigh 0xea
#define AreaParserTaskNum 0x071f
#define ColumnSets 0x071e
#define CurrentPageLoc 0x0725
#define CurrentColumnPos 0x0726
#define BackloadingFlag 0x0728
#define BehindAreaParserFlag 0x0729
#define AreaObjectPageLoc 0x072a
#define AreaObjectPageSel 0x072b
#define AreaDataOffset 0x072c
#define AreaObjOffsetBuffer 0x072d
#define AreaObjectLength 0x0730
#define StaircaseControl 0x0734
#define AreaObjectHeight 0x0735
#define MushroomLedgeHalfLen 0x0736
#define EnemyDataOffset 0x0739
#define EnemyObjectPageLoc 0x073a
#define EnemyObjectPageSel 0x073b
#define MetatileBuffer 0x06a1
#define BlockBufferColumnPos 0x06a0
#define CurrentNTAddr_Low 0x0721
#define CurrentNTAddr_High 0x0720
#define AttributeBuffer 0x03f9
#define LoopCommand 0x0745
#define DisplayDigits 0x07d7
#define TopScoreDisplay 0x07d7
#define ScoreAndCoinDisplay 0x07dd
#define PlayerScoreDisplay 0x07dd
#define GameTimerDisplay 0x07f8
#define DigitModifier 0x0134
#define VerticalFlipFlag 0x0109
#define FloateyNum_Control 0x0110
#define ShellChainCounter 0x0125
#define FloateyNum_Timer 0x012c
#define FloateyNum_X_Pos 0x0117
#define FloateyNum_Y_Pos 0x011e
#define FlagpoleFNum_Y_Pos 0x010d
#define FlagpoleFNum_YMFDummy 0x010e
#define FlagpoleScore 0x010f
#define FlagpoleCollisionYPos 0x070f
#define StompChainCounter 0x0484
#define VRAM_Buffer1_Offset 0x0300
#define VRAM_Buffer1 0x0301
#define VRAM_Buffer2_Offset 0x0340
#define VRAM_Buffer2 0x0341
#define VRAM_Buffer_AddrCtrl 0x0773
#define Sprite0HitDetectFlag 0x0722
#define DisableScreenFlag 0x0774
#define DisableIntermediate 0x0769
#define ColorRotateOffset 0x06d4
#define TerrainControl 0x0727
#define AreaStyle 0x0733
#define ForegroundScenery 0x0741
#define BackgroundScenery 0x0742
#define CloudTypeOverride 0x0743
#define BackgroundColorCtrl 0x0744
#define AreaType 0x074e
#define AreaAddrsLOffset 0x074f
#define AreaPointer 0x0750
#define PlayerEntranceCtrl 0x0710
#define GameTimerSetting 0x0715
#define AltEntranceControl 0x0752
#define EntrancePage 0x0751
#define NumberOfPlayers 0x077a
#define WarpZoneControl 0x06d6
#define ChangeAreaTimer 0x06de
#define MultiLoopCorrectCntr 0x06d9
#define MultiLoopPassCntr 0x06da
#define FetchNewGameTimerFlag 0x0757
#define GameTimerExpiredFlag 0x0759
#define PrimaryHardMode 0x076a
#define SecondaryHardMode 0x06cc
#define WorldSelectNumber 0x076b
#define WorldSelectEnableFlag 0x07fc
#define ContinueWorld 0x07fd
#define CurrentPlayer 0x0753
#define PlayerSize 0x0754
#define PlayerStatus 0x0756
#define OnscreenPlayerInfo 0x075a
#define NumberofLives 0x075a
#define HalfwayPage 0x075b
#define LevelNumber 0x075c
#define Hidden1UpFlag 0x075d
#define CoinTally 0x075e
#define WorldNumber 0x075f
#define AreaNumber 0x0760
#define CoinTallyFor1Ups 0x0748
#define OffscreenPlayerInfo 0x0761
#define OffScr_NumberofLives 0x0761
#define OffScr_HalfwayPage 0x0762
#define OffScr_LevelNumber 0x0763
#define OffScr_Hidden1UpFlag 0x0764
#define OffScr_CoinTally 0x0765
#define OffScr_WorldNumber 0x0766
#define OffScr_AreaNumber 0x0767
#define BalPlatformAlignment 0x03a0
#define Platform_X_Scroll 0x03a1
#define PlatformCollisionFlag 0x03a2
#define YPlatformTopYPos 0x0401
#define YPlatformCenterYPos 0x58
#define BrickCoinTimerFlag 0x06bc
#define StarFlagTaskControl 0x0746
#define PseudoRandomBitReg 0x07a7
#define WarmBootValidation 0x07ff
#define SprShuffleAmtOffset 0x06e0
#define SprShuffleAmt 0x06e1
#define SprDataOffset 0x06e4
#define Player_SprDataOffset 0x06e4
#define Enemy_SprDataOffset 0x06e5
#define Block_SprDataOffset 0x06ec
#define Alt_SprDataOffset 0x06ec
#define Bubble_SprDataOffset 0x06ee
#define FBall_SprDataOffset 0x06f1
#define Misc_SprDataOffset 0x06f3
#define SprDataOffset_Ctrl 0x03ee
#define Player_State 0x1d
#define Enemy_State 0x1e
#define Fireball_State 0x24
#define Block_State 0x26
#define Misc_State 0x2a
#define Player_MovingDir 0x45
#define Enemy_MovingDir 0x46
#define SprObject_X_Speed 0x57
#define Player_X_Speed 0x57
#define Enemy_X_Speed 0x58
#define Fireball_X_Speed 0x5e
#define Block_X_Speed 0x60
#define Misc_X_Speed 0x64
#define Jumpspring_FixedYPos 0x58
#define JumpspringAnimCtrl 0x070e
#define JumpspringForce 0x06db
#define SprObject_PageLoc 0x6d
#define Player_PageLoc 0x6d
#define Enemy_PageLoc 0x6e
#define Fireball_PageLoc 0x74
#define Block_PageLoc 0x76
#define Misc_PageLoc 0x7a
#define Bubble_PageLoc 0x83
#define SprObject_X_Position 0x86
#define Player_X_Position 0x86
#define Enemy_X_Position 0x87
#define Fireball_X_Position 0x8d
#define Block_X_Position 0x8f
#define Misc_X_Position 0x93
#define Bubble_X_Position 0x9c
#define SprObject_Y_Speed 0x9f
#define Player_Y_Speed 0x9f
#define Enemy_Y_Speed 0xa0
#define Fireball_Y_Speed 0xa6
#define Block_Y_Speed 0xa8
#define Misc_Y_Speed 0xac
#define SprObject_Y_HighPos 0xb5
#define Player_Y_HighPos 0xb5
#define Enemy_Y_HighPos 0xb6
#define Fireball_Y_HighPos 0xbc
#define Block_Y_HighPos 0xbe
#define Misc_Y_HighPos 0xc2
#define Bubble_Y_HighPos 0xcb
#define SprObject_Y_Position 0xce
#define Player_Y_Position 0xce
#define Enemy_Y_Position 0xcf
#define Fireball_Y_Position 0xd5
#define Block_Y_Position 0xd7
#define Misc_Y_Position 0xdb
#define Bubble_Y_Position 0xe4
#define SprObject_Rel_XPos 0x03ad
#define Player_Rel_XPos 0x03ad
#define Enemy_Rel_XPos 0x03ae
#define Fireball_Rel_XPos 0x03af
#define Bubble_Rel_XPos 0x03b0
#define Block_Rel_XPos 0x03b1
#define Misc_Rel_XPos 0x03b3
#define SprObject_Rel_YPos 0x03b8
#define Player_Rel_YPos 0x03b8
#define Enemy_Rel_YPos 0x03b9
#define Fireball_Rel_YPos 0x03ba
#define Bubble_Rel_YPos 0x03bb
#define Block_Rel_YPos 0x03bc
#define Misc_Rel_YPos 0x03be
#define SprObject_SprAttrib 0x03c4
#define Player_SprAttrib 0x03c4
#define Enemy_SprAttrib 0x03c5
#define SprObject_X_MoveForce 0x0400
#define Enemy_X_MoveForce 0x0401
#define SprObject_YMF_Dummy 0x0416
#define Player_YMF_Dummy 0x0416
#define Enemy_YMF_Dummy 0x0417
#define Bubble_YMF_Dummy 0x042c
#define SprObject_Y_MoveForce 0x0433
#define Player_Y_MoveForce 0x0433
#define Enemy_Y_MoveForce 0x0434
#define Block_Y_MoveForce 0x043c
#define DisableCollisionDet 0x0716
#define Player_CollisionBits 0x0490
#define Enemy_CollisionBits 0x0491
#define SprObj_BoundBoxCtrl 0x0499
#define Player_BoundBoxCtrl 0x0499
#define Enemy_BoundBoxCtrl 0x049a
#define Fireball_BoundBoxCtrl 0x04a0
#define Misc_BoundBoxCtrl 0x04a2
#define EnemyFrenzyBuffer 0x06cb
#define EnemyFrenzyQueue 0x06cd
#define Enemy_Flag 0x0f
#define Enemy_ID 0x16
#define PlayerGfxOffset 0x06d5
#define Player_XSpeedAbsolute 0x0700
#define FrictionAdderHigh 0x0701
#define FrictionAdderLow 0x0702
#define RunningSpeed 0x0703
#define SwimmingFlag 0x0704
#define Player_X_MoveForce 0x0705
#define DiffToHaltJump 0x0706
#define JumpOrigin_Y_HighPos 0x0707
#define JumpOrigin_Y_Position 0x0708
#define VerticalForce 0x0709
#define VerticalForceDown 0x070a
#define PlayerChangeSizeFlag 0x070b
#define PlayerAnimTimerSet 0x070c
#define PlayerAnimCtrl 0x070d
#define DeathMusicLoaded 0x0712
#define FlagpoleSoundQueue 0x0713
#define CrouchingFlag 0x0714
#define MaximumLeftSpeed 0x0450
#define MaximumRightSpeed 0x0456
#define SprObject_OffscrBits 0x03d0
#define Player_OffscreenBits 0x03d0
#define Enemy_OffscreenBits 0x03d1
#define FBall_OffscreenBits 0x03d2
#define Bubble_OffscreenBits 0x03d3
#define Block_OffscreenBits 0x03d4
#define Misc_OffscreenBits 0x03d6
#define EnemyOffscrBitsMasked 0x03d8
#define Cannon_Offset 0x046a
#define Cannon_PageLoc 0x046b
#define Cannon_X_Position 0x0471
#define Cannon_Y_Position 0x0477
#define Cannon_Timer 0x047d
#define Whirlpool_Offset 0x046a
#define Whirlpool_PageLoc 0x046b
#define Whirlpool_LeftExtent 0x0471
#define Whirlpool_Length 0x0477
#define Whirlpool_Flag 0x047d
#define VineFlagOffset 0x0398
#define VineHeight 0x0399
#define VineObjOffset 0x039a
#define VineStart_Y_Position 0x039d
#define Block_Orig_YPos 0x03e4
#define Block_BBuf_Low 0x03e6
#define Block_Metatile 0x03e8
#define Block_PageLoc2 0x03ea
#define Block_RepFlag 0x03ec
#define Block_ResidualCounter 0x03f0
#define Block_Orig_XPos 0x03f1
#define BoundingBox_UL_XPos 0x04ac
#define BoundingBox_UL_YPos 0x04ad
#define BoundingBox_DR_XPos 0x04ae
#define BoundingBox_DR_YPos 0x04af
#define BoundingBox_UL_Corner 0x04ac
#define BoundingBox_LR_Corner 0x04ae
#define EnemyBoundingBoxCoord 0x04b0
#define PowerUpType 0x39
#define FireballBouncingFlag 0x3a
#define FireballCounter 0x06ce
#define FireballThrowingTimer 0x0711
#define HammerEnemyOffset 0x06ae
#define JumpCoinMiscOffset 0x06b7
#define Block_Buffer_1 0x0500
#define Block_Buffer_2 0x05d0
#define HammerThrowingTimer 0x03a2
#define HammerBroJumpTimer 0x3c
#define Misc_Collision_Flag 0x06be
#define RedPTroopaOrigXPos 0x0401
#define RedPTroopaCenterYPos 0x58
#define XMovePrimaryCounter 0xa0
#define XMoveSecondaryCounter 0x58
#define CheepCheepMoveMFlag 0x58
#define CheepCheepOrigYPos 0x0434
#define BitMFilter 0x06dd
#define LakituReappearTimer 0x06d1
#define LakituMoveSpeed 0x58
#define LakituMoveDirection 0xa0
#define FirebarSpinState_Low 0x58
#define FirebarSpinState_High 0xa0
#define FirebarSpinSpeed 0x0388
#define FirebarSpinDirection 0x34
#define DuplicateObj_Offset 0x06cf
#define NumberofGroupEnemies 0x06d3
#define BlooperMoveCounter 0xa0
#define BlooperMoveSpeed 0x58
#define BowserBodyControls 0x0363
#define BowserFeetCounter 0x0364
#define BowserMovementSpeed 0x0365
#define BowserOrigXPos 0x0366
#define BowserFlameTimerCtrl 0x0367
#define BowserFront_Offset 0x0368
#define BridgeCollapseOffset 0x0369
#define BowserGfxFlag 0x036a
#define BowserHitPoints 0x0483
#define MaxRangeFromOrigin 0x06dc
#define BowserFlamePRandomOfs 0x0417
#define PiranhaPlantUpYPos 0x0417
#define PiranhaPlantDownYPos 0x0434
#define PiranhaPlant_Y_Speed 0x58
#define PiranhaPlant_MoveFlag 0xa0
#define FireworksCounter 0x06d7
#define ExplosionGfxCounter 0x58
#define ExplosionTimerCounter 0xa0
#define Squ2_NoteLenBuffer 0x07b3
#define Squ2_NoteLenCounter 0x07b4
#define Squ2_EnvelopeDataCtrl 0x07b5
#define Squ1_NoteLenCounter 0x07b6
#define Squ1_EnvelopeDataCtrl 0x07b7
#define Tri_NoteLenBuffer 0x07b8
#define Tri_NoteLenCounter 0x07b9
#define Noise_BeatLenCounter 0x07ba
#define Squ1_SfxLenCounter 0x07bb
#define Squ2_SfxLenCounter 0x07bd
#define Sfx_SecondaryCounter 0x07be
#define Noise_SfxLenCounter 0x07bf
#define PauseSoundQueue 0xfa
#define Square1SoundQueue 0xff
#define Square2SoundQueue 0xfe
#define NoiseSoundQueue 0xfd
#define AreaMusicQueue 0xfb
#define EventMusicQueue 0xfc
#define Square1SoundBuffer 0xf1
#define Square2SoundBuffer 0xf2
#define NoiseSoundBuffer 0xf3
#define AreaMusicBuffer 0xf4
#define EventMusicBuffer 0x07b1
#define PauseSoundBuffer 0x07b2
#define MusicData 0xf5
#define MusicDataLow 0xf5
#define MusicDataHigh 0xf6
#define MusicOffset_Square2 0xf7
#define MusicOffset_Square1 0xf8
#define MusicOffset_Triangle 0xf9
#define MusicOffset_Noise 0x07b0
#define NoteLenLookupTblOfs 0xf0
#define DAC_Counter 0x07c0
#define NoiseDataLoopbackOfs 0x07c1
#define NoteLengthTblAdder 0x07c4
#define AreaMusicBuffer_Alt 0x07c5
#define PauseModeFlag 0x07c6
#define GroundMusicHeaderOfs 0x07c7
#define AltRegContentFlag 0x07ca
#define Sfx_SmallJump BOOST_BINARY(10000000)
#define Sfx_Flagpole BOOST_BINARY(01000000)
#define Sfx_Fireball BOOST_BINARY(00100000)
#define Sfx_PipeDown_Injury BOOST_BINARY(00010000)
#define Sfx_EnemySmack BOOST_BINARY(00001000)
#define Sfx_EnemyStomp BOOST_BINARY(00000100)
#define Sfx_Bump BOOST_BINARY(00000010)
#define Sfx_BigJump BOOST_BINARY(00000001)
#define Sfx_BowserFall BOOST_BINARY(10000000)
#define Sfx_ExtraLife BOOST_BINARY(01000000)
#define Sfx_PowerUpGrab BOOST_BINARY(00100000)
#define Sfx_TimerTick BOOST_BINARY(00010000)
#define Sfx_Blast BOOST_BINARY(00001000)
#define Sfx_GrowVine BOOST_BINARY(00000100)
#define Sfx_GrowPowerUp BOOST_BINARY(00000010)
#define Sfx_CoinGrab BOOST_BINARY(00000001)
#define Sfx_BowserFlame BOOST_BINARY(00000010)
#define Sfx_BrickShatter BOOST_BINARY(00000001)
#define Silence BOOST_BINARY(10000000)
#define StarPowerMusic BOOST_BINARY(01000000)
#define PipeIntroMusic BOOST_BINARY(00100000)
#define CloudMusic BOOST_BINARY(00010000)
#define CastleMusic BOOST_BINARY(00001000)
#define UndergroundMusic BOOST_BINARY(00000100)
#define WaterMusic BOOST_BINARY(00000010)
#define GroundMusic BOOST_BINARY(00000001)
#define TimeRunningOutMusic BOOST_BINARY(01000000)
#define EndOfLevelMusic BOOST_BINARY(00100000)
#define AltGameOverMusic BOOST_BINARY(00010000)
#define EndOfCastleMusic BOOST_BINARY(00001000)
#define VictoryMusic BOOST_BINARY(00000100)
#define GameOverMusic BOOST_BINARY(00000010)
#define DeathMusic BOOST_BINARY(00000001)
#define GreenKoopa 0x00
#define BuzzyBeetle 0x02
#define RedKoopa 0x03
#define HammerBro 0x05
#define Goomba 0x06
#define Bloober 0x07
#define BulletBill_FrenzyVar 0x08
#define GreyCheepCheep 0x0a
#define RedCheepCheep 0x0b
#define Podoboo 0x0c
#define PiranhaPlant 0x0d
#define GreenParatroopaJump 0x0e
#define RedParatroopa 0x0f
#define GreenParatroopaFly 0x10
#define Lakitu 0x11
#define Spiny 0x12
#define FlyCheepCheepFrenzy 0x14
#define FlyingCheepCheep 0x14
#define BowserFlame 0x15
#define Fireworks 0x16
#define BBill_CCheep_Frenzy 0x17
#define Stop_Frenzy 0x18
#define Bowser 0x2d
#define PowerUpObject 0x2e
#define VineObject 0x2f
#define FlagpoleFlagObject 0x30
#define StarFlagObject 0x31
#define JumpspringObject 0x32
#define BulletBill_CannonVar 0x33
#define RetainerObject 0x35
#define TallEnemy 0x09
#define World1 0
#define World2 1
#define World3 2
#define World4 3
#define World5 4
#define World6 5
#define World7 6
#define World8 7
#define Level1 0
#define Level2 1
#define Level3 2
#define Level4 3
#define WarmBootOffset LOBYTE(0x07d6)
#define ColdBootOffset LOBYTE(0x07fe)
#define TitleScreenDataOffset 0x1ec0
#define SoundMemory 0x07b0
#define SwimTileRepOffset PlayerGraphicsTable + 0x9e
#define MusicHeaderOffsetData MusicHeaderData - 1
#define MHD MusicHeaderData
#define A_Button BOOST_BINARY(10000000)
#define B_Button BOOST_BINARY(01000000)
#define Select_Button BOOST_BINARY(00100000)
#define Start_Button BOOST_BINARY(00010000)
#define Up_Dir BOOST_BINARY(00001000)
#define Down_Dir BOOST_BINARY(00000100)
#define Left_Dir BOOST_BINARY(00000010)
#define Right_Dir BOOST_BINARY(00000001)
#define TitleScreenModeValue 0
#define GameModeValue 1
#define VictoryModeValue 2
#define GameOverModeValue 3

// Generated Data Addresses
#define VRAM_AddrTable_Low 0x8000
#define VRAM_AddrTable_High 0x8013
#define VRAM_Buffer_Offset 0x8026
#define WSelectBufferTemplate 0x8028
#define MushroomIconData 0x802e
#define DemoActionData 0x8036
#define DemoTimingData 0x804b
#define FloateyNumTileData 0x8061
#define ScoreUpdateData 0x8079
#define AreaPalette 0x8085
#define BGColorCtrl_Addr 0x8089
#define BackgroundColors 0x808d
#define PlayerColors 0x8095
#define GameText 0x80a1
#define TopStatusBarLine 0x80a1
#define WorldLivesDisplay 0x80c8
#define TwoPlayerTimeUp 0x80e7
#define OnePlayerTimeUp 0x80ef
#define TwoPlayerGameOver 0x80fa
#define OnePlayerGameOver 0x8102
#define WarpZoneWelcome 0x810f
#define LuigiName 0x813c
#define WarpZoneNumbers 0x8141
#define GameTextOffsets 0x814d
#define ColorRotatePalette 0x8157
#define BlankPalette 0x815d
#define Palette3Data 0x8165
#define BlockGfxData 0x8175
#define MetatileGraphics_Low 0x8189
#define MetatileGraphics_High 0x818d
#define Palette0_MTiles 0x8191
#define Palette1_MTiles 0x822d
#define Palette2_MTiles 0x82e5
#define Palette3_MTiles 0x830d
#define WaterPaletteData 0x8325
#define GroundPaletteData 0x8349
#define UndergroundPaletteData 0x836d
#define CastlePaletteData 0x8391
#define DaySnowPaletteData 0x83b5
#define NightSnowPaletteData 0x83bd
#define MushroomPaletteData 0x83c5
#define BowserPaletteData 0x83cd
#define MarioThanksMessage 0x83d5
#define LuigiThanksMessage 0x83e9
#define MushroomRetainerSaved 0x83fd
#define PrincessSaved1 0x8429
#define PrincessSaved2 0x8440
#define WorldSelectMessage1 0x845f
#define WorldSelectMessage2 0x8470
#define StatusBarData 0x8485
#define StatusBarOffset 0x8491
#define DefaultSprOffsets 0x8497
#define Sprite0Data 0x84a6
#define MusicSelectData 0x84aa
#define PlayerStarting_X_Pos 0x84b0
#define AltYPosOffset 0x84b4
#define PlayerStarting_Y_Pos 0x84b6
#define PlayerBGPriorityData 0x84bf
#define GameTimerData 0x84c7
#define HalfwayPageNybbles 0x84cb
#define BSceneDataOffsets 0x84db
#define BackSceneryData 0x84de
#define BackSceneryMetatiles 0x856e
#define FSceneDataOffsets 0x8592
#define ForeSceneryData 0x8595
#define TerrainMetatiles 0x85bc
#define TerrainRenderBits 0x85c0
#define BlockBuffLowBounds 0x85e0
#define FrenzyIDData 0x85e4
#define PulleyRopeMetatiles 0x85e7
#define CastleMetatiles 0x85ea
#define SidePipeShaftData 0x8621
#define SidePipeTopPart 0x8625
#define SidePipeBottomPart 0x8629
#define VerticalPipeData 0x862d
#define CoinMetatileData 0x8635
#define C_ObjectRow 0x8639
#define C_ObjectMetatile 0x863c
#define SolidBlockMetatiles 0x863f
#define BrickMetatiles 0x8643
#define StaircaseHeightData 0x8648
#define StaircaseRowData 0x8651
#define HoleMetatiles 0x865a
#define BlockBufferAddr 0x865e
#define AreaDataOfsLoopback 0x8662
#define WorldAddrOffsets 0x866d
#define AreaAddrOffsets 0x8675
#define World1Areas 0x8675
#define World2Areas 0x867a
#define World3Areas 0x867f
#define World4Areas 0x8683
#define World5Areas 0x8688
#define World6Areas 0x868c
#define World7Areas 0x8690
#define World8Areas 0x8695
#define EnemyAddrHOffsets 0x8699
#define EnemyDataAddrLow 0x869d
#define EnemyDataAddrHigh 0x86bf
#define AreaDataHOffsets 0x86e1
#define AreaDataAddrLow 0x86e5
#define AreaDataAddrHigh 0x8707
#define E_CastleArea1 0x8729
#define E_CastleArea2 0x8750
#define E_CastleArea3 0x8769
#define E_CastleArea4 0x8798
#define E_CastleArea5 0x87c3
#define E_CastleArea6 0x87d8
#define E_GroundArea1 0x8812
#define E_GroundArea2 0x8837
#define E_GroundArea3 0x8854
#define E_GroundArea4 0x8862
#define E_GroundArea5 0x8889
#define E_GroundArea6 0x88ba
#define E_GroundArea7 0x88d8
#define E_GroundArea8 0x88f5
#define E_GroundArea9 0x890a
#define E_GroundArea10 0x8934
#define E_GroundArea11 0x8935
#define E_GroundArea12 0x8959
#define E_GroundArea13 0x8962
#define E_GroundArea14 0x8987
#define E_GroundArea15 0x89aa
#define E_GroundArea16 0x89b3
#define E_GroundArea17 0x89b4
#define E_GroundArea18 0x89ee
#define E_GroundArea19 0x8a19
#define E_GroundArea20 0x8a47
#define E_GroundArea21 0x8a63
#define E_GroundArea22 0x8a6c
#define E_UndergroundArea1 0x8a91
#define E_UndergroundArea2 0x8abe
#define E_UndergroundArea3 0x8aec
#define E_WaterArea1 0x8b19
#define E_WaterArea2 0x8b2a
#define E_WaterArea3 0x8b54
#define L_CastleArea1 0x8b68
#define L_CastleArea2 0x8bc9
#define L_CastleArea3 0x8c48
#define L_CastleArea4 0x8cbb
#define L_CastleArea5 0x8d28
#define L_CastleArea6 0x8db3
#define L_GroundArea1 0x8e24
#define L_GroundArea2 0x8e87
#define L_GroundArea3 0x8ef0
#define L_GroundArea4 0x8f43
#define L_GroundArea5 0x8fd2
#define L_GroundArea6 0x9047
#define L_GroundArea7 0x90ac
#define L_GroundArea8 0x9101
#define L_GroundArea9 0x9186
#define L_GroundArea10 0x91eb
#define L_GroundArea11 0x91f4
#define L_GroundArea12 0x9233
#define L_GroundArea13 0x9248
#define L_GroundArea14 0x92af
#define L_GroundArea15 0x9314
#define L_GroundArea16 0x9387
#define L_GroundArea17 0x93b8
#define L_GroundArea18 0x944b
#define L_GroundArea19 0x94be
#define L_GroundArea20 0x9537
#define L_GroundArea21 0x9590
#define L_GroundArea22 0x95bb
#define L_UndergroundArea1 0x95ee
#define L_UndergroundArea2 0x9691
#define L_UndergroundArea3 0x9732
#define L_WaterArea1 0x97bf
#define L_WaterArea2 0x97fe
#define L_WaterArea3 0x9879
#define X_SubtracterData 0x9895
#define OffscrJoypadBitsData 0x9897
#define Hidden1UpCoinAmts 0x9899
#define ClimbAdderLow 0x98a1
#define ClimbAdderHigh 0x98a5
#define JumpMForceData 0x98a9
#define FallMForceData 0x98b0
#define PlayerYSpdData 0x98b7
#define InitMForceData 0x98be
#define MaxLeftXSpdData 0x98c5
#define MaxRightXSpdData 0x98c8
#define FrictionData 0x98cc
#define Climb_Y_SpeedData 0x98cf
#define Climb_Y_MForceData 0x98d2
#define PlayerAnimTmrData 0x98d5
#define FireballXSpdData 0x98d8
#define Bubble_MForceData 0x98da
#define BubbleTimerData 0x98dc
#define FlagpoleScoreMods 0x98de
#define FlagpoleScoreDigits 0x98e3
#define Jumpspring_Y_PosData 0x98e8
#define VineHeightData 0x98ec
#define CannonBitmasks 0x98ee
#define BulletBillXSpdData 0x98f0
#define HammerEnemyOfsData 0x98f2
#define HammerXSpdData 0x98fb
#define CoinTallyOffsets 0x98fd
#define ScoreOffsets 0x98ff
#define StatusBarNybbles 0x9901
#define BlockYPosAdderData 0x9903
#define BrickQBlockMetatiles 0x9905
#define MaxSpdBlockData 0x9913
#define LoopCmdWorldNumber 0x9915
#define LoopCmdPageNumber 0x9920
#define LoopCmdYPosition 0x992b
#define NormalXSpdData 0x9936
#define HBroWalkingTimerData 0x9938
#define PRDiffAdjustData 0x993a
#define FirebarSpinSpdData 0x9946
#define FirebarSpinDirData 0x994b
#define FlyCCXPositionData 0x9950
#define FlyCCXSpeedData 0x9960
#define FlyCCTimerData 0x996c
#define FlameYPosData 0x9970
#define FlameYMFAdderData 0x9974
#define FireworksXPosData 0x9976
#define FireworksYPosData 0x997c
#define Bitmasks 0x9982
#define Enemy17YPosData 0x998a
#define SwimCC_IDData 0x9992
#define PlatPosDataLow 0x9994
#define PlatPosDataHigh 0x9997
#define HammerThrowTmrData 0x999a
#define XSpeedAdderData 0x999c
#define RevivedXSpeed 0x99a0
#define HammerBroJumpLData 0x99a4
#define BlooberBitmasks 0x99a6
#define SwimCCXMoveData 0x99a8
#define FirebarPosLookupTbl 0x99ac
#define FirebarMirrorData 0x9a0f
#define FirebarTblOffsets 0x9a13
#define FirebarYPos 0x9a1f
#define PRandomSubtracter 0x9a21
#define FlyCCBPriority 0x9a26
#define LakituDiffAdj 0x9a2b
#define BridgeCollapseData 0x9a2e
#define PRandomRange 0x9a3d
#define FlameTimerData 0x9a41
#define StarFlagYPosAdder 0x9a49
#define StarFlagXPosAdder 0x9a4d
#define StarFlagTileData 0x9a51
#define BowserIdentities 0x9a55
#define ResidualXSpdData 0x9a5d
#define KickedShellXSpdData 0x9a5f
#define DemotedKoopaXSpdData 0x9a61
#define KickedShellPtsData 0x9a63
#define StompedEnemyPtsData 0x9a66
#define RevivalRateData 0x9a6a
#define SetBitsMask 0x9a6c
#define ClearBitsMask 0x9a73
#define PlayerPosSPlatData 0x9a7a
#define PlayerBGUpperExtent 0x9a7c
#define AreaChangeTimerData 0x9a7e
#define ClimbXPosAdder 0x9a80
#define ClimbPLocAdder 0x9a82
#define FlagpoleYPosData 0x9a84
#define SolidMTileUpperExt 0x9a89
#define ClimbMTileUpperExt 0x9a8d
#define EnemyBGCStateData 0x9a91
#define EnemyBGCXSpdData 0x9a97
#define BoundBoxCtrlData 0x9a99
#define BlockBufferAdderData 0x9ac9
#define BlockBuffer_X_Adder 0x9acc
#define BlockBuffer_Y_Adder 0x9ae8
#define VineYPosAdder 0x9b04
#define FirstSprXPos 0x9b06
#define FirstSprYPos 0x9b0a
#define SecondSprXPos 0x9b0e
#define SecondSprYPos 0x9b12
#define FirstSprTilenum 0x9b16
#define SecondSprTilenum 0x9b1a
#define HammerSprAttrib 0x9b1e
#define FlagpoleScoreNumTiles 0x9b22
#define JumpingCoinTiles 0x9b2c
#define PowerUpGfxTable 0x9b30
#define PowerUpAttributes 0x9b40
#define EnemyGraphicsTable 0x9b44
#define EnemyGfxTableOffsets 0x9c46
#define EnemyAttributeData 0x9c61
#define EnemyAnimTimingBMask 0x9c7c
#define JumpspringFrameOffsets 0x9c7e
#define DefaultBlockObjTiles 0x9c83
#define ExplosionTiles 0x9c87
#define PlayerGfxTblOffsets 0x9c8a
#define PlayerGraphicsTable 0x9c9a
#define SwimKickTileNum 0x9d6a
#define IntermediatePlayerData 0x9d6c
#define ChangeSizeOffsetAdder 0x9d72
#define ObjOffsetData 0x9d86
#define XOffscreenBitsData 0x9d89
#define DefaultXOnscreenOfs 0x9d99
#define YOffscreenBitsData 0x9d9c
#define DefaultYOnscreenOfs 0x9da5
#define HighPosUnitData 0x9da8
#define SwimStompEnvelopeData 0x9daa
#define ExtraLifeFreqData 0x9db8
#define PowerUpGrabFreqData 0x9dbe
#define PUp_VGrow_FreqData 0x9ddc
#define BrickShatterFreqData 0x9dfc
#define MusicHeaderData 0x9e0c
#define TimeRunningOutHdr 0x9e3d
#define Star_CloudHdr 0x9e42
#define EndOfLevelMusHdr 0x9e48
#define ResidualHeaderData 0x9e4d
#define UndergroundMusHdr 0x9e52
#define SilenceHdr 0x9e57
#define CastleMusHdr 0x9e5b
#define VictoryMusHdr 0x9e60
#define GameOverMusHdr 0x9e65
#define WaterMusHdr 0x9e6a
#define WinCastleMusHdr 0x9e70
#define GroundLevelPart1Hdr 0x9e75
#define GroundLevelPart2AHdr 0x9e7b
#define GroundLevelPart2BHdr 0x9e81
#define GroundLevelPart2CHdr 0x9e87
#define GroundLevelPart3AHdr 0x9e8d
#define GroundLevelPart3BHdr 0x9e93
#define GroundLevelLeadInHdr 0x9e99
#define GroundLevelPart4AHdr 0x9e9f
#define GroundLevelPart4BHdr 0x9ea5
#define GroundLevelPart4CHdr 0x9eab
#define DeathMusHdr 0x9eb1
#define Star_CloudMData 0x9eb7
#define GroundM_P1Data 0x9f00
#define SilenceData 0x9f1b
#define GroundM_P2AData 0x9f48
#define GroundM_P2BData 0x9f74
#define GroundM_P2CData 0x9f9c
#define GroundM_P3AData 0x9fc1
#define GroundM_P3BData 0x9fda
#define GroundMLdInData 0x9ff8
#define GroundM_P4AData 0xa024
#define GroundM_P4BData 0xa04a
#define DeathMusData 0xa071
#define GroundM_P4CData 0xa073
#define CastleMusData 0xa0a3
#define GameOverMusData 0xa144
#define TimeRunOutMusData 0xa171
#define WinLevelMusData 0xa1af
#define UndergroundMusData 0xa210
#define WaterMusData 0xa251
#define EndOfCastleMusData 0xa350
#define VictoryMusData 0xa3c7
#define FreqRegLookupTbl 0xa3ff
#define MusicLengthLookupTbl 0xa465
#define EndOfCastleMusicEnvData 0xa495
#define AreaMusicEnvData 0xa499
#define WaterEventMusEnvData 0xa4a1
#define BowserFlameEnvData 0xa4c9
#define BrickShatterEnvData 0xa4e9

// Constant data
static const uint8_t VRAM_AddrTable_Low__data[] = {
    LOBYTE(VRAM_Buffer1), LOBYTE(WaterPaletteData), LOBYTE(GroundPaletteData),
    LOBYTE(UndergroundPaletteData), LOBYTE(CastlePaletteData), LOBYTE(VRAM_Buffer1_Offset),
    LOBYTE(VRAM_Buffer2), LOBYTE(VRAM_Buffer2), LOBYTE(BowserPaletteData),
    LOBYTE(DaySnowPaletteData), LOBYTE(NightSnowPaletteData), LOBYTE(MushroomPaletteData),
    LOBYTE(MarioThanksMessage), LOBYTE(LuigiThanksMessage), LOBYTE(MushroomRetainerSaved),
    LOBYTE(PrincessSaved1), LOBYTE(PrincessSaved2), LOBYTE(WorldSelectMessage1),
    LOBYTE(WorldSelectMessage2)
};

static const uint8_t VRAM_AddrTable_High__data[] = {
    HIBYTE(VRAM_Buffer1), HIBYTE(WaterPaletteData), HIBYTE(GroundPaletteData),
    HIBYTE(UndergroundPaletteData), HIBYTE(CastlePaletteData), HIBYTE(VRAM_Buffer1_Offset),
    HIBYTE(VRAM_Buffer2), HIBYTE(VRAM_Buffer2), HIBYTE(BowserPaletteData),
    HIBYTE(DaySnowPaletteData), HIBYTE(NightSnowPaletteData), HIBYTE(MushroomPaletteData),
    HIBYTE(MarioThanksMessage), HIBYTE(LuigiThanksMessage), HIBYTE(MushroomRetainerSaved),
    HIBYTE(PrincessSaved1), HIBYTE(PrincessSaved2), HIBYTE(WorldSelectMessage1),
    HIBYTE(WorldSelectMessage2)
};

static const uint8_t VRAM_Buffer_Offset__data[] = {
    LOBYTE(VRAM_Buffer1_Offset), LOBYTE(VRAM_Buffer2_Offset)
};

static const uint8_t WSelectBufferTemplate__data[] = {
    0x04, 0x20, 0x73, 0x01, 0x00, 0x00
};

static const uint8_t MushroomIconData__data[] = {
    0x07, 0x22, 0x49, 0x83, 0xce, 0x24, 0x24, 0x00
};

static const uint8_t DemoActionData__data[] = {
    0x01, 0x80, 0x02, 0x81, 0x41, 0x80, 0x01,
    0x42, 0xc2, 0x02, 0x80, 0x41, 0xc1, 0x41, 0xc1,
    0x01, 0xc1, 0x01, 0x02, 0x80, 0x00
};

static const uint8_t DemoTimingData__data[] = {
    0x9b, 0x10, 0x18, 0x05, 0x2c, 0x20, 0x24,
    0x15, 0x5a, 0x10, 0x20, 0x28, 0x30, 0x20, 0x10,
    0x80, 0x20, 0x30, 0x30, 0x01, 0xff, 0x00
};

static const uint8_t FloateyNumTileData__data[] = {
    0xff, 0xff,
    0xf6, 0xfb,
    0xf7, 0xfb,
    0xf8, 0xfb,
    0xf9, 0xfb,
    0xfa, 0xfb,
    0xf6, 0x50,
    0xf7, 0x50,
    0xf8, 0x50,
    0xf9, 0x50,
    0xfa, 0x50,
    0xfd, 0xfe
};

static const uint8_t ScoreUpdateData__data[] = {
    0xff,
    0x41, 0x42, 0x44, 0x45, 0x48,
    0x31, 0x32, 0x34, 0x35, 0x38, 0x00
};

static const uint8_t AreaPalette__data[] = {
    0x01, 0x02, 0x03, 0x04
};

static const uint8_t BGColorCtrl_Addr__data[] = {
    0x00, 0x09, 0x0a, 0x04
};

static const uint8_t BackgroundColors__data[] = {
    0x22, 0x22, 0x0f, 0x0f,
    0x0f, 0x22, 0x0f, 0x0f
};

static const uint8_t PlayerColors__data[] = {
    0x22, 0x16, 0x27, 0x18,
    0x22, 0x30, 0x27, 0x19,
    0x22, 0x37, 0x27, 0x16
};

static const uint8_t* GameText__data = nullptr;
static const uint8_t TopStatusBarLine__data[] = {
    0x20, 0x43, 0x05, 0x16, 0x0a, 0x1b, 0x12, 0x18,
    0x20, 0x52, 0x0b, 0x20, 0x18, 0x1b, 0x15, 0x0d,
    0x24, 0x24, 0x1d, 0x12, 0x16, 0x0e,
    0x20, 0x68, 0x05, 0x00, 0x24, 0x24, 0x2e, 0x29,
    0x23, 0xc0, 0x7f, 0xaa,
    0x23, 0xc2, 0x01, 0xea,
    0xff
};

static const uint8_t WorldLivesDisplay__data[] = {
    0x21, 0xcd, 0x07, 0x24, 0x24,
    0x29, 0x24, 0x24, 0x24, 0x24,
    0x21, 0x4b, 0x09, 0x20, 0x18,
    0x1b, 0x15, 0x0d, 0x24, 0x24, 0x28, 0x24,
    0x22, 0x0c, 0x47, 0x24,
    0x23, 0xdc, 0x01, 0xba,
    0xff
};

static const uint8_t TwoPlayerTimeUp__data[] = {
    0x21, 0xcd, 0x05, 0x16, 0x0a, 0x1b, 0x12, 0x18
};

static const uint8_t OnePlayerTimeUp__data[] = {
    0x22, 0x0c, 0x07, 0x1d, 0x12, 0x16, 0x0e, 0x24, 0x1e, 0x19,
    0xff
};

static const uint8_t TwoPlayerGameOver__data[] = {
    0x21, 0xcd, 0x05, 0x16, 0x0a, 0x1b, 0x12, 0x18
};

static const uint8_t OnePlayerGameOver__data[] = {
    0x22, 0x0b, 0x09, 0x10, 0x0a, 0x16, 0x0e, 0x24,
    0x18, 0x1f, 0x0e, 0x1b,
    0xff
};

static const uint8_t WarpZoneWelcome__data[] = {
    0x25, 0x84, 0x15, 0x20, 0x0e, 0x15, 0x0c, 0x18, 0x16,
    0x0e, 0x24, 0x1d, 0x18, 0x24, 0x20, 0x0a, 0x1b, 0x19,
    0x24, 0x23, 0x18, 0x17, 0x0e, 0x2b,
    0x26, 0x25, 0x01, 0x24,
    0x26, 0x2d, 0x01, 0x24,
    0x26, 0x35, 0x01, 0x24,
    0x27, 0xd9, 0x46, 0xaa,
    0x27, 0xe1, 0x45, 0xaa,
    0xff
};

static const uint8_t LuigiName__data[] = {
    0x15, 0x1e, 0x12, 0x10, 0x12
};

static const uint8_t WarpZoneNumbers__data[] = {
    0x04, 0x03, 0x02, 0x00,
    0x24, 0x05, 0x24, 0x00,
    0x08, 0x07, 0x06, 0x00
};

static const uint8_t GameTextOffsets__data[] = {
    TopStatusBarLine - GameText, TopStatusBarLine - GameText,
    WorldLivesDisplay - GameText, WorldLivesDisplay - GameText,
    TwoPlayerTimeUp - GameText, OnePlayerTimeUp - GameText,
    TwoPlayerGameOver - GameText, OnePlayerGameOver - GameText,
    WarpZoneWelcome - GameText, WarpZoneWelcome - GameText
};

static const uint8_t ColorRotatePalette__data[] = {
    0x27, 0x27, 0x27, 0x17, 0x07, 0x17
};

static const uint8_t BlankPalette__data[] = {
    0x3f, 0x0c, 0x04, 0xff, 0xff, 0xff, 0xff, 0x00
};

static const uint8_t Palette3Data__data[] = {
    0x0f, 0x07, 0x12, 0x0f,
    0x0f, 0x07, 0x17, 0x0f,
    0x0f, 0x07, 0x17, 0x1c,
    0x0f, 0x07, 0x17, 0x00
};

static const uint8_t BlockGfxData__data[] = {
    0x45, 0x45, 0x47, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x57, 0x58, 0x59, 0x5a,
    0x24, 0x24, 0x24, 0x24,
    0x26, 0x26, 0x26, 0x26
};

static const uint8_t MetatileGraphics_Low__data[] = {
    LOBYTE(Palette0_MTiles), LOBYTE(Palette1_MTiles), LOBYTE(Palette2_MTiles), LOBYTE(Palette3_MTiles)
};

static const uint8_t MetatileGraphics_High__data[] = {
    HIBYTE(Palette0_MTiles), HIBYTE(Palette1_MTiles), HIBYTE(Palette2_MTiles), HIBYTE(Palette3_MTiles)
};

static const uint8_t Palette0_MTiles__data[] = {
    0x24, 0x24, 0x24, 0x24,
    0x27, 0x27, 0x27, 0x27,
    0x24, 0x24, 0x24, 0x35,
    0x36, 0x25, 0x37, 0x25,
    0x24, 0x38, 0x24, 0x24,
    0x24, 0x30, 0x30, 0x26,
    0x26, 0x26, 0x34, 0x26,
    0x24, 0x31, 0x24, 0x32,
    0x33, 0x26, 0x24, 0x33,
    0x34, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26,
    0x24, 0xc0, 0x24, 0xc0,
    0x24, 0x7f, 0x7f, 0x24,
    0xb8, 0xba, 0xb9, 0xbb,
    0xb8, 0xbc, 0xb9, 0xbd,
    0xba, 0xbc, 0xbb, 0xbd,
    0x60, 0x64, 0x61, 0x65,
    0x62, 0x66, 0x63, 0x67,
    0x60, 0x64, 0x61, 0x65,
    0x62, 0x66, 0x63, 0x67,
    0x68, 0x68, 0x69, 0x69,
    0x26, 0x26, 0x6a, 0x6a,
    0x4b, 0x4c, 0x4d, 0x4e,
    0x4d, 0x4f, 0x4d, 0x4f,
    0x4d, 0x4e, 0x50, 0x51,
    0x6b, 0x70, 0x2c, 0x2d,
    0x6c, 0x71, 0x6d, 0x72,
    0x6e, 0x73, 0x6f, 0x74,
    0x86, 0x8a, 0x87, 0x8b,
    0x88, 0x8c, 0x88, 0x8c,
    0x89, 0x8d, 0x69, 0x69,
    0x8e, 0x91, 0x8f, 0x92,
    0x26, 0x93, 0x26, 0x93,
    0x90, 0x94, 0x69, 0x69,
    0xa4, 0xe9, 0xea, 0xeb,
    0x24, 0x24, 0x24, 0x24,
    0x24, 0x2f, 0x24, 0x3d,
    0xa2, 0xa2, 0xa3, 0xa3,
    0x24, 0x24, 0x24, 0x24
};

static const uint8_t Palette1_MTiles__data[] = {
    0xa2, 0xa2, 0xa3, 0xa3,
    0x99, 0x24, 0x99, 0x24,
    0x24, 0xa2, 0x3e, 0x3f,
    0x5b, 0x5c, 0x24, 0xa3,
    0x24, 0x24, 0x24, 0x24,
    0x9d, 0x47, 0x9e, 0x47,
    0x47, 0x47, 0x27, 0x27,
    0x47, 0x47, 0x47, 0x47,
    0x27, 0x27, 0x47, 0x47,
    0xa9, 0x47, 0xaa, 0x47,
    0x9b, 0x27, 0x9c, 0x27,
    0x27, 0x27, 0x27, 0x27,
    0x52, 0x52, 0x52, 0x52,
    0x80, 0xa0, 0x81, 0xa1,
    0xbe, 0xbe, 0xbf, 0xbf,
    0x75, 0xba, 0x76, 0xbb,
    0xba, 0xba, 0xbb, 0xbb,
    0x45, 0x47, 0x45, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x45, 0x47, 0x45, 0x47,
    0xb4, 0xb6, 0xb5, 0xb7,
    0x45, 0x47, 0x45, 0x47,
    0x45, 0x47, 0x45, 0x47,
    0x45, 0x47, 0x45, 0x47,
    0x45, 0x47, 0x45, 0x47,
    0x45, 0x47, 0x45, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x47, 0x47, 0x47, 0x47,
    0x24, 0x24, 0x24, 0x24,
    0x24, 0x24, 0x24, 0x24,
    0xab, 0xac, 0xad, 0xae,
    0x5d, 0x5e, 0x5d, 0x5e,
    0xc1, 0x24, 0xc1, 0x24,
    0xc6, 0xc8, 0xc7, 0xc9,
    0xca, 0xcc, 0xcb, 0xcd,
    0x2a, 0x2a, 0x40, 0x40,
    0x24, 0x24, 0x24, 0x24,
    0x24, 0x47, 0x24, 0x47,
    0x82, 0x83, 0x84, 0x85,
    0x24, 0x47, 0x24, 0x47,
    0x86, 0x8a, 0x87, 0x8b,
    0x8e, 0x91, 0x8f, 0x92,
    0x24, 0x2f, 0x24, 0x3d
};

static const uint8_t Palette2_MTiles__data[] = {
    0x24, 0x24, 0x24, 0x35,
    0x36, 0x25, 0x37, 0x25,
    0x24, 0x38, 0x24, 0x24,
    0x24, 0x24, 0x39, 0x24,
    0x3a, 0x24, 0x3b, 0x24,
    0x3c, 0x24, 0x24, 0x24,
    0x41, 0x26, 0x41, 0x26,
    0x26, 0x26, 0x26, 0x26,
    0xb0, 0xb1, 0xb2, 0xb3,
    0x77, 0x79, 0x77, 0x79
};

static const uint8_t Palette3_MTiles__data[] = {
    0x53, 0x55, 0x54, 0x56,
    0x53, 0x55, 0x54, 0x56,
    0xa5, 0xa7, 0xa6, 0xa8,
    0xc2, 0xc4, 0xc3, 0xc5,
    0x57, 0x59, 0x58, 0x5a,
    0x7b, 0x7d, 0x7c, 0x7e
};

static const uint8_t WaterPaletteData__data[] = {
    0x3f, 0x00, 0x20,
    0x0f, 0x15, 0x12, 0x25,
    0x0f, 0x3a, 0x1a, 0x0f,
    0x0f, 0x30, 0x12, 0x0f,
    0x0f, 0x27, 0x12, 0x0f,
    0x22, 0x16, 0x27, 0x18,
    0x0f, 0x10, 0x30, 0x27,
    0x0f, 0x16, 0x30, 0x27,
    0x0f, 0x0f, 0x30, 0x10,
    0x00
};

static const uint8_t GroundPaletteData__data[] = {
    0x3f, 0x00, 0x20,
    0x0f, 0x29, 0x1a, 0x0f,
    0x0f, 0x36, 0x17, 0x0f,
    0x0f, 0x30, 0x21, 0x0f,
    0x0f, 0x27, 0x17, 0x0f,
    0x0f, 0x16, 0x27, 0x18,
    0x0f, 0x1a, 0x30, 0x27,
    0x0f, 0x16, 0x30, 0x27,
    0x0f, 0x0f, 0x36, 0x17,
    0x00
};

static const uint8_t UndergroundPaletteData__data[] = {
    0x3f, 0x00, 0x20,
    0x0f, 0x29, 0x1a, 0x09,
    0x0f, 0x3c, 0x1c, 0x0f,
    0x0f, 0x30, 0x21, 0x1c,
    0x0f, 0x27, 0x17, 0x1c,
    0x0f, 0x16, 0x27, 0x18,
    0x0f, 0x1c, 0x36, 0x17,
    0x0f, 0x16, 0x30, 0x27,
    0x0f, 0x0c, 0x3c, 0x1c,
    0x00
};

static const uint8_t CastlePaletteData__data[] = {
    0x3f, 0x00, 0x20,
    0x0f, 0x30, 0x10, 0x00,
    0x0f, 0x30, 0x10, 0x00,
    0x0f, 0x30, 0x16, 0x00,
    0x0f, 0x27, 0x17, 0x00,
    0x0f, 0x16, 0x27, 0x18,
    0x0f, 0x1c, 0x36, 0x17,
    0x0f, 0x16, 0x30, 0x27,
    0x0f, 0x00, 0x30, 0x10,
    0x00
};

static const uint8_t DaySnowPaletteData__data[] = {
    0x3f, 0x00, 0x04,
    0x22, 0x30, 0x00, 0x10,
    0x00
};

static const uint8_t NightSnowPaletteData__data[] = {
    0x3f, 0x00, 0x04,
    0x0f, 0x30, 0x00, 0x10,
    0x00
};

static const uint8_t MushroomPaletteData__data[] = {
    0x3f, 0x00, 0x04,
    0x22, 0x27, 0x16, 0x0f,
    0x00
};

static const uint8_t BowserPaletteData__data[] = {
    0x3f, 0x14, 0x04,
    0x0f, 0x1a, 0x30, 0x27,
    0x00
};

static const uint8_t MarioThanksMessage__data[] = {
    0x25, 0x48, 0x10,
    0x1d, 0x11, 0x0a, 0x17, 0x14, 0x24,
    0x22, 0x18, 0x1e, 0x24,
    0x16, 0x0a, 0x1b, 0x12, 0x18, 0x2b,
    0x00
};

static const uint8_t LuigiThanksMessage__data[] = {
    0x25, 0x48, 0x10,
    0x1d, 0x11, 0x0a, 0x17, 0x14, 0x24,
    0x22, 0x18, 0x1e, 0x24,
    0x15, 0x1e, 0x12, 0x10, 0x12, 0x2b,
    0x00
};

static const uint8_t MushroomRetainerSaved__data[] = {
    0x25, 0xc5, 0x16,
    0x0b, 0x1e, 0x1d, 0x24, 0x18, 0x1e, 0x1b, 0x24,
    0x19, 0x1b, 0x12, 0x17, 0x0c, 0x0e, 0x1c, 0x1c, 0x24,
    0x12, 0x1c, 0x24, 0x12, 0x17,
    0x26, 0x05, 0x0f,
    0x0a, 0x17, 0x18, 0x1d, 0x11, 0x0e, 0x1b, 0x24,
    0x0c, 0x0a, 0x1c, 0x1d, 0x15, 0x0e, 0x2b, 0x00
};

static const uint8_t PrincessSaved1__data[] = {
    0x25, 0xa7, 0x13,
    0x22, 0x18, 0x1e, 0x1b, 0x24,
    0x1a, 0x1e, 0x0e, 0x1c, 0x1d, 0x24,
    0x12, 0x1c, 0x24, 0x18, 0x1f, 0x0e, 0x1b, 0xaf,
    0x00
};

static const uint8_t PrincessSaved2__data[] = {
    0x25, 0xe3, 0x1b,
    0x20, 0x0e, 0x24,
    0x19, 0x1b, 0x0e, 0x1c, 0x0e, 0x17, 0x1d, 0x24,
    0x22, 0x18, 0x1e, 0x24, 0x0a, 0x24, 0x17, 0x0e, 0x20, 0x24,
    0x1a, 0x1e, 0x0e, 0x1c, 0x1d, 0xaf,
    0x00
};

static const uint8_t WorldSelectMessage1__data[] = {
    0x26, 0x4a, 0x0d,
    0x19, 0x1e, 0x1c, 0x11, 0x24,
    0x0b, 0x1e, 0x1d, 0x1d, 0x18, 0x17, 0x24, 0x0b,
    0x00
};

static const uint8_t WorldSelectMessage2__data[] = {
    0x26, 0x88, 0x11,
    0x1d, 0x18, 0x24, 0x1c, 0x0e, 0x15, 0x0e, 0x0c, 0x1d, 0x24,
    0x0a, 0x24, 0x20, 0x18, 0x1b, 0x15, 0x0d,
    0x00
};

static const uint8_t StatusBarData__data[] = {
    0xf0, 0x06,
    0x62, 0x06,
    0x62, 0x06,
    0x6d, 0x02,
    0x6d, 0x02,
    0x7a, 0x03
};

static const uint8_t StatusBarOffset__data[] = {
    0x06, 0x0c, 0x12, 0x18, 0x1e, 0x24
};

static const uint8_t DefaultSprOffsets__data[] = {
    0x04, 0x30, 0x48, 0x60, 0x78, 0x90, 0xa8, 0xc0,
    0xd8, 0xe8, 0x24, 0xf8, 0xfc, 0x28, 0x2c
};

static const uint8_t Sprite0Data__data[] = {
    0x18, 0xff, 0x23, 0x58
};

static const uint8_t MusicSelectData__data[] = {
    WaterMusic, GroundMusic, UndergroundMusic, CastleMusic,
    CloudMusic, PipeIntroMusic
};

static const uint8_t PlayerStarting_X_Pos__data[] = {
    0x28, 0x18,
    0x38, 0x28
};

static const uint8_t AltYPosOffset__data[] = {
    0x08, 0x00
};

static const uint8_t PlayerStarting_Y_Pos__data[] = {
    0x00, 0x20, 0xb0, 0x50, 0x00, 0x00, 0xb0, 0xb0,
    0xf0
};

static const uint8_t PlayerBGPriorityData__data[] = {
    0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t GameTimerData__data[] = {
    0x20,
    0x04, 0x03, 0x02
};

static const uint8_t HalfwayPageNybbles__data[] = {
    0x56, 0x40,
    0x65, 0x70,
    0x66, 0x40,
    0x66, 0x40,
    0x66, 0x40,
    0x66, 0x60,
    0x65, 0x70,
    0x00, 0x00
};

static const uint8_t BSceneDataOffsets__data[] = {
    0x00, 0x30, 0x60
};

static const uint8_t BackSceneryData__data[] = {
    0x93, 0x00, 0x00, 0x11, 0x12, 0x12, 0x13, 0x00,
    0x00, 0x51, 0x52, 0x53, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x02, 0x02, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x91, 0x92, 0x93, 0x00,
    0x00, 0x00, 0x00, 0x51, 0x52, 0x53, 0x41, 0x42,
    0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x92,
    0x97, 0x87, 0x88, 0x89, 0x99, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x13, 0xa4, 0xa5, 0xa5, 0xa5, 0xa6,
    0x97, 0x98, 0x99, 0x01, 0x02, 0x03, 0x00, 0xa4,
    0xa5, 0xa6, 0x00, 0x11, 0x12, 0x12, 0x12, 0x13,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x03,
    0x00, 0xa4, 0xa5, 0xa5, 0xa6, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x9c, 0x00, 0x8b, 0xaa, 0xaa,
    0xaa, 0xaa, 0x11, 0x12, 0x13, 0x8b, 0x00, 0x9c,
    0x9c, 0x00, 0x00, 0x01, 0x02, 0x03, 0x11, 0x12,
    0x12, 0x13, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa,
    0x9c, 0xaa, 0x00, 0x8b, 0x00, 0x01, 0x02, 0x03
};

static const uint8_t BackSceneryMetatiles__data[] = {
    0x80, 0x83, 0x00,
    0x81, 0x84, 0x00,
    0x82, 0x85, 0x00,
    0x02, 0x00, 0x00,
    0x03, 0x00, 0x00,
    0x04, 0x00, 0x00,
    0x00, 0x05, 0x06,
    0x07, 0x06, 0x0a,
    0x00, 0x08, 0x09,
    0x4d, 0x00, 0x00,
    0x0d, 0x0f, 0x4e,
    0x0e, 0x4e, 0x4e
};

static const uint8_t FSceneDataOffsets__data[] = {
    0x00, 0x0d, 0x1a
};

static const uint8_t ForeSceneryData__data[] = {
    0x86, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
    0x87, 0x87, 0x87, 0x87, 0x69, 0x69,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x47,
    0x47, 0x47, 0x47, 0x47, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x86, 0x87
};

static const uint8_t TerrainMetatiles__data[] = {
    0x69, 0x54, 0x52, 0x62
};

static const uint8_t TerrainRenderBits__data[] = {
    BOOST_BINARY(00000000), BOOST_BINARY(00000000),
    BOOST_BINARY(00000000), BOOST_BINARY(00011000),
    BOOST_BINARY(00000001), BOOST_BINARY(00011000),
    BOOST_BINARY(00000111), BOOST_BINARY(00011000),
    BOOST_BINARY(00001111), BOOST_BINARY(00011000),
    BOOST_BINARY(11111111), BOOST_BINARY(00011000),
    BOOST_BINARY(00000001), BOOST_BINARY(00011111),
    BOOST_BINARY(00000111), BOOST_BINARY(00011111),
    BOOST_BINARY(00001111), BOOST_BINARY(00011111),
    BOOST_BINARY(10000001), BOOST_BINARY(00011111),
    BOOST_BINARY(00000001), BOOST_BINARY(00000000),
    BOOST_BINARY(10001111), BOOST_BINARY(00011111),
    BOOST_BINARY(11110001), BOOST_BINARY(00011111),
    BOOST_BINARY(11111001), BOOST_BINARY(00011000),
    BOOST_BINARY(11110001), BOOST_BINARY(00011000),
    BOOST_BINARY(11111111), BOOST_BINARY(00011111)
};

static const uint8_t BlockBuffLowBounds__data[] = {
    0x10, 0x51, 0x88, 0xc0
};

static const uint8_t FrenzyIDData__data[] = {
    FlyCheepCheepFrenzy, BBill_CCheep_Frenzy, Stop_Frenzy
};

static const uint8_t PulleyRopeMetatiles__data[] = {
    0x42, 0x41, 0x43
};

static const uint8_t CastleMetatiles__data[] = {
    0x00, 0x45, 0x45, 0x45, 0x00,
    0x00, 0x48, 0x47, 0x46, 0x00,
    0x45, 0x49, 0x49, 0x49, 0x45,
    0x47, 0x47, 0x4a, 0x47, 0x47,
    0x47, 0x47, 0x4b, 0x47, 0x47,
    0x49, 0x49, 0x49, 0x49, 0x49,
    0x47, 0x4a, 0x47, 0x4a, 0x47,
    0x47, 0x4b, 0x47, 0x4b, 0x47,
    0x47, 0x47, 0x47, 0x47, 0x47,
    0x4a, 0x47, 0x4a, 0x47, 0x4a,
    0x4b, 0x47, 0x4b, 0x47, 0x4b
};

static const uint8_t SidePipeShaftData__data[] = {
    0x15, 0x14,
    0x00, 0x00
};

static const uint8_t SidePipeTopPart__data[] = {
    0x15, 0x1e,
    0x1d, 0x1c
};

static const uint8_t SidePipeBottomPart__data[] = {
    0x15, 0x21,
    0x20, 0x1f
};

static const uint8_t VerticalPipeData__data[] = {
    0x11, 0x10,
    0x15, 0x14,
    0x13, 0x12,
    0x15, 0x14
};

static const uint8_t CoinMetatileData__data[] = {
    0xc3, 0xc2, 0xc2, 0xc2
};

static const uint8_t C_ObjectRow__data[] = {
    0x06, 0x07, 0x08
};

static const uint8_t C_ObjectMetatile__data[] = {
    0xc5, 0x0c, 0x89
};

static const uint8_t SolidBlockMetatiles__data[] = {
    0x69, 0x61, 0x61, 0x62
};

static const uint8_t BrickMetatiles__data[] = {
    0x22, 0x51, 0x52, 0x52,
    0x88
};

static const uint8_t StaircaseHeightData__data[] = {
    0x07, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
};

static const uint8_t StaircaseRowData__data[] = {
    0x03, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a
};

static const uint8_t HoleMetatiles__data[] = {
    0x87, 0x00, 0x00, 0x00
};

static const uint8_t BlockBufferAddr__data[] = {
    LOBYTE(Block_Buffer_1), LOBYTE(Block_Buffer_2),
    HIBYTE(Block_Buffer_1), HIBYTE(Block_Buffer_2)
};

static const uint8_t AreaDataOfsLoopback__data[] = {
    0x12, 0x36, 0x0e, 0x0e, 0x0e, 0x32, 0x32, 0x32, 0x0a, 0x26, 0x40
};

static const uint8_t WorldAddrOffsets__data[] = {
    World1Areas - AreaAddrOffsets, World2Areas - AreaAddrOffsets,
    World3Areas - AreaAddrOffsets, World4Areas - AreaAddrOffsets,
    World5Areas - AreaAddrOffsets, World6Areas - AreaAddrOffsets,
    World7Areas - AreaAddrOffsets, World8Areas - AreaAddrOffsets
};

static const uint8_t* AreaAddrOffsets__data = nullptr;
static const uint8_t World1Areas__data[] = {
    0x25, 0x29, 0xc0, 0x26, 0x60
};

static const uint8_t World2Areas__data[] = {
    0x28, 0x29, 0x01, 0x27, 0x62
};

static const uint8_t World3Areas__data[] = {
    0x24, 0x35, 0x20, 0x63
};

static const uint8_t World4Areas__data[] = {
    0x22, 0x29, 0x41, 0x2c, 0x61
};

static const uint8_t World5Areas__data[] = {
    0x2a, 0x31, 0x26, 0x62
};

static const uint8_t World6Areas__data[] = {
    0x2e, 0x23, 0x2d, 0x60
};

static const uint8_t World7Areas__data[] = {
    0x33, 0x29, 0x01, 0x27, 0x64
};

static const uint8_t World8Areas__data[] = {
    0x30, 0x32, 0x21, 0x65
};

static const uint8_t EnemyAddrHOffsets__data[] = {
    0x1f, 0x06, 0x1c, 0x00
};

static const uint8_t EnemyDataAddrLow__data[] = {
    LOBYTE(E_CastleArea1), LOBYTE(E_CastleArea2), LOBYTE(E_CastleArea3), LOBYTE(E_CastleArea4), LOBYTE(E_CastleArea5), LOBYTE(E_CastleArea6),
    LOBYTE(E_GroundArea1), LOBYTE(E_GroundArea2), LOBYTE(E_GroundArea3), LOBYTE(E_GroundArea4), LOBYTE(E_GroundArea5), LOBYTE(E_GroundArea6),
    LOBYTE(E_GroundArea7), LOBYTE(E_GroundArea8), LOBYTE(E_GroundArea9), LOBYTE(E_GroundArea10), LOBYTE(E_GroundArea11), LOBYTE(E_GroundArea12),
    LOBYTE(E_GroundArea13), LOBYTE(E_GroundArea14), LOBYTE(E_GroundArea15), LOBYTE(E_GroundArea16), LOBYTE(E_GroundArea17), LOBYTE(E_GroundArea18),
    LOBYTE(E_GroundArea19), LOBYTE(E_GroundArea20), LOBYTE(E_GroundArea21), LOBYTE(E_GroundArea22), LOBYTE(E_UndergroundArea1),
    LOBYTE(E_UndergroundArea2), LOBYTE(E_UndergroundArea3), LOBYTE(E_WaterArea1), LOBYTE(E_WaterArea2), LOBYTE(E_WaterArea3)
};

static const uint8_t EnemyDataAddrHigh__data[] = {
    HIBYTE(E_CastleArea1), HIBYTE(E_CastleArea2), HIBYTE(E_CastleArea3), HIBYTE(E_CastleArea4), HIBYTE(E_CastleArea5), HIBYTE(E_CastleArea6),
    HIBYTE(E_GroundArea1), HIBYTE(E_GroundArea2), HIBYTE(E_GroundArea3), HIBYTE(E_GroundArea4), HIBYTE(E_GroundArea5), HIBYTE(E_GroundArea6),
    HIBYTE(E_GroundArea7), HIBYTE(E_GroundArea8), HIBYTE(E_GroundArea9), HIBYTE(E_GroundArea10), HIBYTE(E_GroundArea11), HIBYTE(E_GroundArea12),
    HIBYTE(E_GroundArea13), HIBYTE(E_GroundArea14), HIBYTE(E_GroundArea15), HIBYTE(E_GroundArea16), HIBYTE(E_GroundArea17), HIBYTE(E_GroundArea18),
    HIBYTE(E_GroundArea19), HIBYTE(E_GroundArea20), HIBYTE(E_GroundArea21), HIBYTE(E_GroundArea22), HIBYTE(E_UndergroundArea1),
    HIBYTE(E_UndergroundArea2), HIBYTE(E_UndergroundArea3), HIBYTE(E_WaterArea1), HIBYTE(E_WaterArea2), HIBYTE(E_WaterArea3)
};

static const uint8_t AreaDataHOffsets__data[] = {
    0x00, 0x03, 0x19, 0x1c
};

static const uint8_t AreaDataAddrLow__data[] = {
    LOBYTE(L_WaterArea1), LOBYTE(L_WaterArea2), LOBYTE(L_WaterArea3), LOBYTE(L_GroundArea1), LOBYTE(L_GroundArea2), LOBYTE(L_GroundArea3),
    LOBYTE(L_GroundArea4), LOBYTE(L_GroundArea5), LOBYTE(L_GroundArea6), LOBYTE(L_GroundArea7), LOBYTE(L_GroundArea8), LOBYTE(L_GroundArea9),
    LOBYTE(L_GroundArea10), LOBYTE(L_GroundArea11), LOBYTE(L_GroundArea12), LOBYTE(L_GroundArea13), LOBYTE(L_GroundArea14), LOBYTE(L_GroundArea15),
    LOBYTE(L_GroundArea16), LOBYTE(L_GroundArea17), LOBYTE(L_GroundArea18), LOBYTE(L_GroundArea19), LOBYTE(L_GroundArea20), LOBYTE(L_GroundArea21),
    LOBYTE(L_GroundArea22), LOBYTE(L_UndergroundArea1), LOBYTE(L_UndergroundArea2), LOBYTE(L_UndergroundArea3), LOBYTE(L_CastleArea1),
    LOBYTE(L_CastleArea2), LOBYTE(L_CastleArea3), LOBYTE(L_CastleArea4), LOBYTE(L_CastleArea5), LOBYTE(L_CastleArea6)
};

static const uint8_t AreaDataAddrHigh__data[] = {
    HIBYTE(L_WaterArea1), HIBYTE(L_WaterArea2), HIBYTE(L_WaterArea3), HIBYTE(L_GroundArea1), HIBYTE(L_GroundArea2), HIBYTE(L_GroundArea3),
    HIBYTE(L_GroundArea4), HIBYTE(L_GroundArea5), HIBYTE(L_GroundArea6), HIBYTE(L_GroundArea7), HIBYTE(L_GroundArea8), HIBYTE(L_GroundArea9),
    HIBYTE(L_GroundArea10), HIBYTE(L_GroundArea11), HIBYTE(L_GroundArea12), HIBYTE(L_GroundArea13), HIBYTE(L_GroundArea14), HIBYTE(L_GroundArea15),
    HIBYTE(L_GroundArea16), HIBYTE(L_GroundArea17), HIBYTE(L_GroundArea18), HIBYTE(L_GroundArea19), HIBYTE(L_GroundArea20), HIBYTE(L_GroundArea21),
    HIBYTE(L_GroundArea22), HIBYTE(L_UndergroundArea1), HIBYTE(L_UndergroundArea2), HIBYTE(L_UndergroundArea3), HIBYTE(L_CastleArea1),
    HIBYTE(L_CastleArea2), HIBYTE(L_CastleArea3), HIBYTE(L_CastleArea4), HIBYTE(L_CastleArea5), HIBYTE(L_CastleArea6)
};

static const uint8_t E_CastleArea1__data[] = {
    0x76, 0xdd, 0xbb, 0x4c, 0xea, 0x1d, 0x1b, 0xcc, 0x56, 0x5d,
    0x16, 0x9d, 0xc6, 0x1d, 0x36, 0x9d, 0xc9, 0x1d, 0x04, 0xdb,
    0x49, 0x1d, 0x84, 0x1b, 0xc9, 0x5d, 0x88, 0x95, 0x0f, 0x08,
    0x30, 0x4c, 0x78, 0x2d, 0xa6, 0x28, 0x90, 0xb5,
    0xff
};

static const uint8_t E_CastleArea2__data[] = {
    0x0f, 0x03, 0x56, 0x1b, 0xc9, 0x1b, 0x0f, 0x07, 0x36, 0x1b,
    0xaa, 0x1b, 0x48, 0x95, 0x0f, 0x0a, 0x2a, 0x1b, 0x5b, 0x0c,
    0x78, 0x2d, 0x90, 0xb5,
    0xff
};

static const uint8_t E_CastleArea3__data[] = {
    0x0b, 0x8c, 0x4b, 0x4c, 0x77, 0x5f, 0xeb, 0x0c, 0xbd, 0xdb,
    0x19, 0x9d, 0x75, 0x1d, 0x7d, 0x5b, 0xd9, 0x1d, 0x3d, 0xdd,
    0x99, 0x1d, 0x26, 0x9d, 0x5a, 0x2b, 0x8a, 0x2c, 0xca, 0x1b,
    0x20, 0x95, 0x7b, 0x5c, 0xdb, 0x4c, 0x1b, 0xcc, 0x3b, 0xcc,
    0x78, 0x2d, 0xa6, 0x28, 0x90, 0xb5,
    0xff
};

static const uint8_t E_CastleArea4__data[] = {
    0x0b, 0x8c, 0x3b, 0x1d, 0x8b, 0x1d, 0xab, 0x0c, 0xdb, 0x1d,
    0x0f, 0x03, 0x65, 0x1d, 0x6b, 0x1b, 0x05, 0x9d, 0x0b, 0x1b,
    0x05, 0x9b, 0x0b, 0x1d, 0x8b, 0x0c, 0x1b, 0x8c, 0x70, 0x15,
    0x7b, 0x0c, 0xdb, 0x0c, 0x0f, 0x08, 0x78, 0x2d, 0xa6, 0x28,
    0x90, 0xb5,
    0xff
};

static const uint8_t E_CastleArea5__data[] = {
    0x27, 0xa9, 0x4b, 0x0c, 0x68, 0x29, 0x0f, 0x06, 0x77, 0x1b,
    0x0f, 0x0b, 0x60, 0x15, 0x4b, 0x8c, 0x78, 0x2d, 0x90, 0xb5,
    0xff
};

static const uint8_t E_CastleArea6__data[] = {
    0x0f, 0x03, 0x8e, 0x65, 0xe1, 0xbb, 0x38, 0x6d, 0xa8, 0x3e, 0xe5, 0xe7,
    0x0f, 0x08, 0x0b, 0x02, 0x2b, 0x02, 0x5e, 0x65, 0xe1, 0xbb, 0x0e,
    0xdb, 0x0e, 0xbb, 0x8e, 0xdb, 0x0e, 0xfe, 0x65, 0xec, 0x0f, 0x0d,
    0x4e, 0x65, 0xe1, 0x0f, 0x0e, 0x4e, 0x02, 0xe0, 0x0f, 0x10, 0xfe, 0xe5, 0xe1,
    0x1b, 0x85, 0x7b, 0x0c, 0x5b, 0x95, 0x78, 0x2d, 0x90, 0xb5,
    0xff
};

static const uint8_t E_GroundArea1__data[] = {
    0xa5, 0x86, 0xe4, 0x28, 0x18, 0xa8, 0x45, 0x83, 0x69, 0x03,
    0xc6, 0x29, 0x9b, 0x83, 0x16, 0xa4, 0x88, 0x24, 0xe9, 0x28,
    0x05, 0xa8, 0x7b, 0x28, 0x24, 0x8f, 0xc8, 0x03, 0xe8, 0x03,
    0x46, 0xa8, 0x85, 0x24, 0xc8, 0x24,
    0xff
};

static const uint8_t E_GroundArea2__data[] = {
    0xeb, 0x8e, 0x0f, 0x03, 0xfb, 0x05, 0x17, 0x85, 0xdb, 0x8e,
    0x0f, 0x07, 0x57, 0x05, 0x7b, 0x05, 0x9b, 0x80, 0x2b, 0x85,
    0xfb, 0x05, 0x0f, 0x0b, 0x1b, 0x05, 0x9b, 0x05,
    0xff
};

static const uint8_t E_GroundArea3__data[] = {
    0x2e, 0xc2, 0x66, 0xe2, 0x11, 0x0f, 0x07, 0x02, 0x11, 0x0f, 0x0c,
    0x12, 0x11,
    0xff
};

static const uint8_t E_GroundArea4__data[] = {
    0x0e, 0xc2, 0xa8, 0xab, 0x00, 0xbb, 0x8e, 0x6b, 0x82, 0xde, 0x00, 0xa0,
    0x33, 0x86, 0x43, 0x06, 0x3e, 0xb4, 0xa0, 0xcb, 0x02, 0x0f, 0x07,
    0x7e, 0x42, 0xa6, 0x83, 0x02, 0x0f, 0x0a, 0x3b, 0x02, 0xcb, 0x37,
    0x0f, 0x0c, 0xe3, 0x0e,
    0xff
};

static const uint8_t E_GroundArea5__data[] = {
    0x9b, 0x8e, 0xca, 0x0e, 0xee, 0x42, 0x44, 0x5b, 0x86, 0x80, 0xb8,
    0x1b, 0x80, 0x50, 0xba, 0x10, 0xb7, 0x5b, 0x00, 0x17, 0x85,
    0x4b, 0x05, 0xfe, 0x34, 0x40, 0xb7, 0x86, 0xc6, 0x06, 0x5b, 0x80,
    0x83, 0x00, 0xd0, 0x38, 0x5b, 0x8e, 0x8a, 0x0e, 0xa6, 0x00,
    0xbb, 0x0e, 0xc5, 0x80, 0xf3, 0x00,
    0xff
};

static const uint8_t E_GroundArea6__data[] = {
    0x1e, 0xc2, 0x00, 0x6b, 0x06, 0x8b, 0x86, 0x63, 0xb7, 0x0f, 0x05,
    0x03, 0x06, 0x23, 0x06, 0x4b, 0xb7, 0xbb, 0x00, 0x5b, 0xb7,
    0xfb, 0x37, 0x3b, 0xb7, 0x0f, 0x0b, 0x1b, 0x37,
    0xff
};

static const uint8_t E_GroundArea7__data[] = {
    0x2b, 0xd7, 0xe3, 0x03, 0xc2, 0x86, 0xe2, 0x06, 0x76, 0xa5,
    0xa3, 0x8f, 0x03, 0x86, 0x2b, 0x57, 0x68, 0x28, 0xe9, 0x28,
    0xe5, 0x83, 0x24, 0x8f, 0x36, 0xa8, 0x5b, 0x03,
    0xff
};

static const uint8_t E_GroundArea8__data[] = {
    0x0f, 0x02, 0x78, 0x40, 0x48, 0xce, 0xf8, 0xc3, 0xf8, 0xc3,
    0x0f, 0x07, 0x7b, 0x43, 0xc6, 0xd0, 0x0f, 0x8a, 0xc8, 0x50,
    0xff
};

static const uint8_t E_GroundArea9__data[] = {
    0x85, 0x86, 0x0b, 0x80, 0x1b, 0x00, 0xdb, 0x37, 0x77, 0x80,
    0xeb, 0x37, 0xfe, 0x2b, 0x20, 0x2b, 0x80, 0x7b, 0x38, 0xab, 0xb8,
    0x77, 0x86, 0xfe, 0x42, 0x20, 0x49, 0x86, 0x8b, 0x06, 0x9b, 0x80,
    0x7b, 0x8e, 0x5b, 0xb7, 0x9b, 0x0e, 0xbb, 0x0e, 0x9b, 0x80
};

static const uint8_t E_GroundArea10__data[] = {
    0xff
};

static const uint8_t E_GroundArea11__data[] = {
    0x0b, 0x80, 0x60, 0x38, 0x10, 0xb8, 0xc0, 0x3b, 0xdb, 0x8e,
    0x40, 0xb8, 0xf0, 0x38, 0x7b, 0x8e, 0xa0, 0xb8, 0xc0, 0xb8,
    0xfb, 0x00, 0xa0, 0xb8, 0x30, 0xbb, 0xee, 0x42, 0x88, 0x0f, 0x0b,
    0x2b, 0x0e, 0x67, 0x0e,
    0xff
};

static const uint8_t E_GroundArea12__data[] = {
    0x0a, 0xaa, 0x0e, 0x28, 0x2a, 0x0e, 0x31, 0x88,
    0xff
};

static const uint8_t E_GroundArea13__data[] = {
    0xc7, 0x83, 0xd7, 0x03, 0x42, 0x8f, 0x7a, 0x03, 0x05, 0xa4,
    0x78, 0x24, 0xa6, 0x25, 0xe4, 0x25, 0x4b, 0x83, 0xe3, 0x03,
    0x05, 0xa4, 0x89, 0x24, 0xb5, 0x24, 0x09, 0xa4, 0x65, 0x24,
    0xc9, 0x24, 0x0f, 0x08, 0x85, 0x25,
    0xff
};

static const uint8_t E_GroundArea14__data[] = {
    0xcd, 0xa5, 0xb5, 0xa8, 0x07, 0xa8, 0x76, 0x28, 0xcc, 0x25,
    0x65, 0xa4, 0xa9, 0x24, 0xe5, 0x24, 0x19, 0xa4, 0x0f, 0x07,
    0x95, 0x28, 0xe6, 0x24, 0x19, 0xa4, 0xd7, 0x29, 0x16, 0xa9,
    0x58, 0x29, 0x97, 0x29,
    0xff
};

static const uint8_t E_GroundArea15__data[] = {
    0x0f, 0x02, 0x02, 0x11, 0x0f, 0x07, 0x02, 0x11,
    0xff
};

static const uint8_t E_GroundArea16__data[] = {
    0xff
};

static const uint8_t E_GroundArea17__data[] = {
    0x2b, 0x82, 0xab, 0x38, 0xde, 0x42, 0xe2, 0x1b, 0xb8, 0xeb,
    0x3b, 0xdb, 0x80, 0x8b, 0xb8, 0x1b, 0x82, 0xfb, 0xb8, 0x7b,
    0x80, 0xfb, 0x3c, 0x5b, 0xbc, 0x7b, 0xb8, 0x1b, 0x8e, 0xcb,
    0x0e, 0x1b, 0x8e, 0x0f, 0x0d, 0x2b, 0x3b, 0xbb, 0xb8, 0xeb, 0x82,
    0x4b, 0xb8, 0xbb, 0x38, 0x3b, 0xb7, 0xbb, 0x02, 0x0f, 0x13,
    0x1b, 0x00, 0xcb, 0x80, 0x6b, 0xbc,
    0xff
};

static const uint8_t E_GroundArea18__data[] = {
    0x7b, 0x80, 0xae, 0x00, 0x80, 0x8b, 0x8e, 0xe8, 0x05, 0xf9, 0x86,
    0x17, 0x86, 0x16, 0x85, 0x4e, 0x2b, 0x80, 0xab, 0x8e, 0x87, 0x85,
    0xc3, 0x05, 0x8b, 0x82, 0x9b, 0x02, 0xab, 0x02, 0xbb, 0x86,
    0xcb, 0x06, 0xd3, 0x03, 0x3b, 0x8e, 0x6b, 0x0e, 0xa7, 0x8e,
    0xff
};

static const uint8_t E_GroundArea19__data[] = {
    0x29, 0x8e, 0x52, 0x11, 0x83, 0x0e, 0x0f, 0x03, 0x9b, 0x0e,
    0x2b, 0x8e, 0x5b, 0x0e, 0xcb, 0x8e, 0xfb, 0x0e, 0xfb, 0x82,
    0x9b, 0x82, 0xbb, 0x02, 0xfe, 0x42, 0xe8, 0xbb, 0x8e, 0x0f, 0x0a,
    0xab, 0x0e, 0xcb, 0x0e, 0xf9, 0x0e, 0x88, 0x86, 0xa6, 0x06,
    0xdb, 0x02, 0xb6, 0x8e,
    0xff
};

static const uint8_t E_GroundArea20__data[] = {
    0xab, 0xce, 0xde, 0x42, 0xc0, 0xcb, 0xce, 0x5b, 0x8e, 0x1b, 0xce,
    0x4b, 0x85, 0x67, 0x45, 0x0f, 0x07, 0x2b, 0x00, 0x7b, 0x85,
    0x97, 0x05, 0x0f, 0x0a, 0x92, 0x02,
    0xff
};

static const uint8_t E_GroundArea21__data[] = {
    0x0a, 0xaa, 0x0e, 0x24, 0x4a, 0x1e, 0x23, 0xaa,
    0xff
};

static const uint8_t E_GroundArea22__data[] = {
    0x1b, 0x80, 0xbb, 0x38, 0x4b, 0xbc, 0xeb, 0x3b, 0x0f, 0x04,
    0x2b, 0x00, 0xab, 0x38, 0xeb, 0x00, 0xcb, 0x8e, 0xfb, 0x80,
    0xab, 0xb8, 0x6b, 0x80, 0xfb, 0x3c, 0x9b, 0xbb, 0x5b, 0xbc,
    0xfb, 0x00, 0x6b, 0xb8, 0xfb, 0x38,
    0xff
};

static const uint8_t E_UndergroundArea1__data[] = {
    0x0b, 0x86, 0x1a, 0x06, 0xdb, 0x06, 0xde, 0xc2, 0x02, 0xf0, 0x3b,
    0xbb, 0x80, 0xeb, 0x06, 0x0b, 0x86, 0x93, 0x06, 0xf0, 0x39,
    0x0f, 0x06, 0x60, 0xb8, 0x1b, 0x86, 0xa0, 0xb9, 0xb7, 0x27,
    0xbd, 0x27, 0x2b, 0x83, 0xa1, 0x26, 0xa9, 0x26, 0xee, 0x25, 0x0b,
    0x27, 0xb4,
    0xff
};

static const uint8_t E_UndergroundArea2__data[] = {
    0x0f, 0x02, 0x1e, 0x2f, 0x60, 0xe0, 0x3a, 0xa5, 0xa7, 0xdb, 0x80,
    0x3b, 0x82, 0x8b, 0x02, 0xfe, 0x42, 0x68, 0x70, 0xbb, 0x25, 0xa7,
    0x2c, 0x27, 0xb2, 0x26, 0xb9, 0x26, 0x9b, 0x80, 0xa8, 0x82,
    0xb5, 0x27, 0xbc, 0x27, 0xb0, 0xbb, 0x3b, 0x82, 0x87, 0x34,
    0xee, 0x25, 0x6b,
    0xff
};

static const uint8_t E_UndergroundArea3__data[] = {
    0x1e, 0xa5, 0x0a, 0x2e, 0x28, 0x27, 0x2e, 0x33, 0xc7, 0x0f, 0x03, 0x1e, 0x40, 0x07,
    0x2e, 0x30, 0xe7, 0x0f, 0x05, 0x1e, 0x24, 0x44, 0x0f, 0x07, 0x1e, 0x22, 0x6a,
    0x2e, 0x23, 0xab, 0x0f, 0x09, 0x1e, 0x41, 0x68, 0x1e, 0x2a, 0x8a, 0x2e, 0x23, 0xa2,
    0x2e, 0x32, 0xea,
    0xff
};

static const uint8_t E_WaterArea1__data[] = {
    0x3b, 0x87, 0x66, 0x27, 0xcc, 0x27, 0xee, 0x31, 0x87, 0xee, 0x23, 0xa7,
    0x3b, 0x87, 0xdb, 0x07,
    0xff
};

static const uint8_t E_WaterArea2__data[] = {
    0x0f, 0x01, 0x2e, 0x25, 0x2b, 0x2e, 0x25, 0x4b, 0x4e, 0x25, 0xcb, 0x6b, 0x07,
    0x97, 0x47, 0xe9, 0x87, 0x47, 0xc7, 0x7a, 0x07, 0xd6, 0xc7,
    0x78, 0x07, 0x38, 0x87, 0xab, 0x47, 0xe3, 0x07, 0x9b, 0x87,
    0x0f, 0x09, 0x68, 0x47, 0xdb, 0xc7, 0x3b, 0xc7,
    0xff
};

static const uint8_t E_WaterArea3__data[] = {
    0x47, 0x9b, 0xcb, 0x07, 0xfa, 0x1d, 0x86, 0x9b, 0x3a, 0x87,
    0x56, 0x07, 0x88, 0x1b, 0x07, 0x9d, 0x2e, 0x65, 0xf0,
    0xff
};

static const uint8_t L_CastleArea1__data[] = {
    0x9b, 0x07,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0xce, 0x03, 0xdc, 0x51,
    0xee, 0x07, 0x73, 0xe0, 0x74, 0x0a, 0x7e, 0x06, 0x9e, 0x0a,
    0xce, 0x06, 0xe4, 0x00, 0xe8, 0x0a, 0xfe, 0x0a, 0x2e, 0x89,
    0x4e, 0x0b, 0x54, 0x0a, 0x14, 0x8a, 0xc4, 0x0a, 0x34, 0x8a,
    0x7e, 0x06, 0xc7, 0x0a, 0x01, 0xe0, 0x02, 0x0a, 0x47, 0x0a,
    0x81, 0x60, 0x82, 0x0a, 0xc7, 0x0a, 0x0e, 0x87, 0x7e, 0x02,
    0xa7, 0x02, 0xb3, 0x02, 0xd7, 0x02, 0xe3, 0x02, 0x07, 0x82,
    0x13, 0x02, 0x3e, 0x06, 0x7e, 0x02, 0xae, 0x07, 0xfe, 0x0a,
    0x0d, 0xc4, 0xcd, 0x43, 0xce, 0x09, 0xde, 0x0b, 0xdd, 0x42,
    0xfe, 0x02, 0x5d, 0xc7,
    0xfd
};

static const uint8_t L_CastleArea2__data[] = {
    0x5b, 0x07,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0x5e, 0x0a, 0x68, 0x64,
    0x98, 0x64, 0xa8, 0x64, 0xce, 0x06, 0xfe, 0x02, 0x0d, 0x01,
    0x1e, 0x0e, 0x7e, 0x02, 0x94, 0x63, 0xb4, 0x63, 0xd4, 0x63,
    0xf4, 0x63, 0x14, 0xe3, 0x2e, 0x0e, 0x5e, 0x02, 0x64, 0x35,
    0x88, 0x72, 0xbe, 0x0e, 0x0d, 0x04, 0xae, 0x02, 0xce, 0x08,
    0xcd, 0x4b, 0xfe, 0x02, 0x0d, 0x05, 0x68, 0x31, 0x7e, 0x0a,
    0x96, 0x31, 0xa9, 0x63, 0xa8, 0x33, 0xd5, 0x30, 0xee, 0x02,
    0xe6, 0x62, 0xf4, 0x61, 0x04, 0xb1, 0x08, 0x3f, 0x44, 0x33,
    0x94, 0x63, 0xa4, 0x31, 0xe4, 0x31, 0x04, 0xbf, 0x08, 0x3f,
    0x04, 0xbf, 0x08, 0x3f, 0xcd, 0x4b, 0x03, 0xe4, 0x0e, 0x03,
    0x2e, 0x01, 0x7e, 0x06, 0xbe, 0x02, 0xde, 0x06, 0xfe, 0x0a,
    0x0d, 0xc4, 0xcd, 0x43, 0xce, 0x09, 0xde, 0x0b, 0xdd, 0x42,
    0xfe, 0x02, 0x5d, 0xc7,
    0xfd
};

static const uint8_t L_CastleArea3__data[] = {
    0x9b, 0x07,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0xfe, 0x00, 0x27, 0xb1,
    0x65, 0x32, 0x75, 0x0a, 0x71, 0x00, 0xb7, 0x31, 0x08, 0xe4,
    0x18, 0x64, 0x1e, 0x04, 0x57, 0x3b, 0xbb, 0x0a, 0x17, 0x8a,
    0x27, 0x3a, 0x73, 0x0a, 0x7b, 0x0a, 0xd7, 0x0a, 0xe7, 0x3a,
    0x3b, 0x8a, 0x97, 0x0a, 0xfe, 0x08, 0x24, 0x8a, 0x2e, 0x00,
    0x3e, 0x40, 0x38, 0x64, 0x6f, 0x00, 0x9f, 0x00, 0xbe, 0x43,
    0xc8, 0x0a, 0xc9, 0x63, 0xce, 0x07, 0xfe, 0x07, 0x2e, 0x81,
    0x66, 0x42, 0x6a, 0x42, 0x79, 0x0a, 0xbe, 0x00, 0xc8, 0x64,
    0xf8, 0x64, 0x08, 0xe4, 0x2e, 0x07, 0x7e, 0x03, 0x9e, 0x07,
    0xbe, 0x03, 0xde, 0x07, 0xfe, 0x0a, 0x03, 0xa5, 0x0d, 0x44,
    0xcd, 0x43, 0xce, 0x09, 0xdd, 0x42, 0xde, 0x0b, 0xfe, 0x02,
    0x5d, 0xc7,
    0xfd
};

static const uint8_t L_CastleArea4__data[] = {
    0x9b, 0x07,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0xfe, 0x06, 0x0c, 0x81,
    0x39, 0x0a, 0x5c, 0x01, 0x89, 0x0a, 0xac, 0x01, 0xd9, 0x0a,
    0xfc, 0x01, 0x2e, 0x83, 0xa7, 0x01, 0xb7, 0x00, 0xc7, 0x01,
    0xde, 0x0a, 0xfe, 0x02, 0x4e, 0x83, 0x5a, 0x32, 0x63, 0x0a,
    0x69, 0x0a, 0x7e, 0x02, 0xee, 0x03, 0xfa, 0x32, 0x03, 0x8a,
    0x09, 0x0a, 0x1e, 0x02, 0xee, 0x03, 0xfa, 0x32, 0x03, 0x8a,
    0x09, 0x0a, 0x14, 0x42, 0x1e, 0x02, 0x7e, 0x0a, 0x9e, 0x07,
    0xfe, 0x0a, 0x2e, 0x86, 0x5e, 0x0a, 0x8e, 0x06, 0xbe, 0x0a,
    0xee, 0x07, 0x3e, 0x83, 0x5e, 0x07, 0xfe, 0x0a, 0x0d, 0xc4,
    0x41, 0x52, 0x51, 0x52, 0xcd, 0x43, 0xce, 0x09, 0xde, 0x0b,
    0xdd, 0x42, 0xfe, 0x02, 0x5d, 0xc7,
    0xfd
};

static const uint8_t L_CastleArea5__data[] = {
    0x5b, 0x07,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0xfe, 0x0a, 0xae, 0x86,
    0xbe, 0x07, 0xfe, 0x02, 0x0d, 0x02, 0x27, 0x32, 0x46, 0x61,
    0x55, 0x62, 0x5e, 0x0e, 0x1e, 0x82, 0x68, 0x3c, 0x74, 0x3a,
    0x7d, 0x4b, 0x5e, 0x8e, 0x7d, 0x4b, 0x7e, 0x82, 0x84, 0x62,
    0x94, 0x61, 0xa4, 0x31, 0xbd, 0x4b, 0xce, 0x06, 0xfe, 0x02,
    0x0d, 0x06, 0x34, 0x31, 0x3e, 0x0a, 0x64, 0x32, 0x75, 0x0a,
    0x7b, 0x61, 0xa4, 0x33, 0xae, 0x02, 0xde, 0x0e, 0x3e, 0x82,
    0x64, 0x32, 0x78, 0x32, 0xb4, 0x36, 0xc8, 0x36, 0xdd, 0x4b,
    0x44, 0xb2, 0x58, 0x32, 0x94, 0x63, 0xa4, 0x3e, 0xba, 0x30,
    0xc9, 0x61, 0xce, 0x06, 0xdd, 0x4b, 0xce, 0x86, 0xdd, 0x4b,
    0xfe, 0x02, 0x2e, 0x86, 0x5e, 0x02, 0x7e, 0x06, 0xfe, 0x02,
    0x1e, 0x86, 0x3e, 0x02, 0x5e, 0x06, 0x7e, 0x02, 0x9e, 0x06,
    0xfe, 0x0a, 0x0d, 0xc4, 0xcd, 0x43, 0xce, 0x09, 0xde, 0x0b,
    0xdd, 0x42, 0xfe, 0x02, 0x5d, 0xc7,
    0xfd
};

static const uint8_t L_CastleArea6__data[] = {
    0x5b, 0x06,
    0x05, 0x32, 0x06, 0x33, 0x07, 0x34, 0x5e, 0x0a, 0xae, 0x02,
    0x0d, 0x01, 0x39, 0x73, 0x0d, 0x03, 0x39, 0x7b, 0x4d, 0x4b,
    0xde, 0x06, 0x1e, 0x8a, 0xae, 0x06, 0xc4, 0x33, 0x16, 0xfe,
    0xa5, 0x77, 0xfe, 0x02, 0xfe, 0x82, 0x0d, 0x07, 0x39, 0x73,
    0xa8, 0x74, 0xed, 0x4b, 0x49, 0xfb, 0xe8, 0x74, 0xfe, 0x0a,
    0x2e, 0x82, 0x67, 0x02, 0x84, 0x7a, 0x87, 0x31, 0x0d, 0x0b,
    0xfe, 0x02, 0x0d, 0x0c, 0x39, 0x73, 0x5e, 0x06, 0xc6, 0x76,
    0x45, 0xff, 0xbe, 0x0a, 0xdd, 0x48, 0xfe, 0x06, 0x3d, 0xcb,
    0x46, 0x7e, 0xad, 0x4a, 0xfe, 0x82, 0x39, 0xf3, 0xa9, 0x7b,
    0x4e, 0x8a, 0x9e, 0x07, 0xfe, 0x0a, 0x0d, 0xc4, 0xcd, 0x43,
    0xce, 0x09, 0xde, 0x0b, 0xdd, 0x42, 0xfe, 0x02, 0x5d, 0xc7,
    0xfd
};

static const uint8_t L_GroundArea1__data[] = {
    0x94, 0x11,
    0x0f, 0x26, 0xfe, 0x10, 0x28, 0x94, 0x65, 0x15, 0xeb, 0x12,
    0xfa, 0x41, 0x4a, 0x96, 0x54, 0x40, 0xa4, 0x42, 0xb7, 0x13,
    0xe9, 0x19, 0xf5, 0x15, 0x11, 0x80, 0x47, 0x42, 0x71, 0x13,
    0x80, 0x41, 0x15, 0x92, 0x1b, 0x1f, 0x24, 0x40, 0x55, 0x12,
    0x64, 0x40, 0x95, 0x12, 0xa4, 0x40, 0xd2, 0x12, 0xe1, 0x40,
    0x13, 0xc0, 0x2c, 0x17, 0x2f, 0x12, 0x49, 0x13, 0x83, 0x40,
    0x9f, 0x14, 0xa3, 0x40, 0x17, 0x92, 0x83, 0x13, 0x92, 0x41,
    0xb9, 0x14, 0xc5, 0x12, 0xc8, 0x40, 0xd4, 0x40, 0x4b, 0x92,
    0x78, 0x1b, 0x9c, 0x94, 0x9f, 0x11, 0xdf, 0x14, 0xfe, 0x11,
    0x7d, 0xc1, 0x9e, 0x42, 0xcf, 0x20,
    0xfd
};

static const uint8_t L_GroundArea2__data[] = {
    0x90, 0xb1,
    0x0f, 0x26, 0x29, 0x91, 0x7e, 0x42, 0xfe, 0x40, 0x28, 0x92,
    0x4e, 0x42, 0x2e, 0xc0, 0x57, 0x73, 0xc3, 0x25, 0xc7, 0x27,
    0x23, 0x84, 0x33, 0x20, 0x5c, 0x01, 0x77, 0x63, 0x88, 0x62,
    0x99, 0x61, 0xaa, 0x60, 0xbc, 0x01, 0xee, 0x42, 0x4e, 0xc0,
    0x69, 0x11, 0x7e, 0x42, 0xde, 0x40, 0xf8, 0x62, 0x0e, 0xc2,
    0xae, 0x40, 0xd7, 0x63, 0xe7, 0x63, 0x33, 0xa7, 0x37, 0x27,
    0x43, 0x04, 0xcc, 0x01, 0xe7, 0x73, 0x0c, 0x81, 0x3e, 0x42,
    0x0d, 0x0a, 0x5e, 0x40, 0x88, 0x72, 0xbe, 0x42, 0xe7, 0x87,
    0xfe, 0x40, 0x39, 0xe1, 0x4e, 0x00, 0x69, 0x60, 0x87, 0x60,
    0xa5, 0x60, 0xc3, 0x31, 0xfe, 0x31, 0x6d, 0xc1, 0xbe, 0x42,
    0xef, 0x20,
    0xfd
};

static const uint8_t L_GroundArea3__data[] = {
    0x52, 0x21,
    0x0f, 0x20, 0x6e, 0x40, 0x58, 0xf2, 0x93, 0x01, 0x97, 0x00,
    0x0c, 0x81, 0x97, 0x40, 0xa6, 0x41, 0xc7, 0x40, 0x0d, 0x04,
    0x03, 0x01, 0x07, 0x01, 0x23, 0x01, 0x27, 0x01, 0xec, 0x03,
    0xac, 0xf3, 0xc3, 0x03, 0x78, 0xe2, 0x94, 0x43, 0x47, 0xf3,
    0x74, 0x43, 0x47, 0xfb, 0x74, 0x43, 0x2c, 0xf1, 0x4c, 0x63,
    0x47, 0x00, 0x57, 0x21, 0x5c, 0x01, 0x7c, 0x72, 0x39, 0xf1,
    0xec, 0x02, 0x4c, 0x81, 0xd8, 0x62, 0xec, 0x01, 0x0d, 0x0d,
    0x0f, 0x38, 0xc7, 0x07, 0xed, 0x4a, 0x1d, 0xc1, 0x5f, 0x26,
    0xfd
};

static const uint8_t L_GroundArea4__data[] = {
    0x54, 0x21,
    0x0f, 0x26, 0xa7, 0x22, 0x37, 0xfb, 0x73, 0x20, 0x83, 0x07,
    0x87, 0x02, 0x93, 0x20, 0xc7, 0x73, 0x04, 0xf1, 0x06, 0x31,
    0x39, 0x71, 0x59, 0x71, 0xe7, 0x73, 0x37, 0xa0, 0x47, 0x04,
    0x86, 0x7c, 0xe5, 0x71, 0xe7, 0x31, 0x33, 0xa4, 0x39, 0x71,
    0xa9, 0x71, 0xd3, 0x23, 0x08, 0xf2, 0x13, 0x05, 0x27, 0x02,
    0x49, 0x71, 0x75, 0x75, 0xe8, 0x72, 0x67, 0xf3, 0x99, 0x71,
    0xe7, 0x20, 0xf4, 0x72, 0xf7, 0x31, 0x17, 0xa0, 0x33, 0x20,
    0x39, 0x71, 0x73, 0x28, 0xbc, 0x05, 0x39, 0xf1, 0x79, 0x71,
    0xa6, 0x21, 0xc3, 0x06, 0xd3, 0x20, 0xdc, 0x00, 0xfc, 0x00,
    0x07, 0xa2, 0x13, 0x21, 0x5f, 0x32, 0x8c, 0x00, 0x98, 0x7a,
    0xc7, 0x63, 0xd9, 0x61, 0x03, 0xa2, 0x07, 0x22, 0x74, 0x72,
    0x77, 0x31, 0xe7, 0x73, 0x39, 0xf1, 0x58, 0x72, 0x77, 0x73,
    0xd8, 0x72, 0x7f, 0xb1, 0x97, 0x73, 0xb6, 0x64, 0xc5, 0x65,
    0xd4, 0x66, 0xe3, 0x67, 0xf3, 0x67, 0x8d, 0xc1, 0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea5__data[] = {
    0x52, 0x31,
    0x0f, 0x20, 0x6e, 0x66, 0x07, 0x81, 0x36, 0x01, 0x66, 0x00,
    0xa7, 0x22, 0x08, 0xf2, 0x67, 0x7b, 0xdc, 0x02, 0x98, 0xf2,
    0xd7, 0x20, 0x39, 0xf1, 0x9f, 0x33, 0xdc, 0x27, 0xdc, 0x57,
    0x23, 0x83, 0x57, 0x63, 0x6c, 0x51, 0x87, 0x63, 0x99, 0x61,
    0xa3, 0x06, 0xb3, 0x21, 0x77, 0xf3, 0xf3, 0x21, 0xf7, 0x2a,
    0x13, 0x81, 0x23, 0x22, 0x53, 0x00, 0x63, 0x22, 0xe9, 0x0b,
    0x0c, 0x83, 0x13, 0x21, 0x16, 0x22, 0x33, 0x05, 0x8f, 0x35,
    0xec, 0x01, 0x63, 0xa0, 0x67, 0x20, 0x73, 0x01, 0x77, 0x01,
    0x83, 0x20, 0x87, 0x20, 0xb3, 0x20, 0xb7, 0x20, 0xc3, 0x01,
    0xc7, 0x00, 0xd3, 0x20, 0xd7, 0x20, 0x67, 0xa0, 0x77, 0x07,
    0x87, 0x22, 0xe8, 0x62, 0xf5, 0x65, 0x1c, 0x82, 0x7f, 0x38,
    0x8d, 0xc1, 0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea6__data[] = {
    0x50, 0x21,
    0x07, 0x81, 0x47, 0x24, 0x57, 0x00, 0x63, 0x01, 0x77, 0x01,
    0xc9, 0x71, 0x68, 0xf2, 0xe7, 0x73, 0x97, 0xfb, 0x06, 0x83,
    0x5c, 0x01, 0xd7, 0x22, 0xe7, 0x00, 0x03, 0xa7, 0x6c, 0x02,
    0xb3, 0x22, 0xe3, 0x01, 0xe7, 0x07, 0x47, 0xa0, 0x57, 0x06,
    0xa7, 0x01, 0xd3, 0x00, 0xd7, 0x01, 0x07, 0x81, 0x67, 0x20,
    0x93, 0x22, 0x03, 0xa3, 0x1c, 0x61, 0x17, 0x21, 0x6f, 0x33,
    0xc7, 0x63, 0xd8, 0x62, 0xe9, 0x61, 0xfa, 0x60, 0x4f, 0xb3,
    0x87, 0x63, 0x9c, 0x01, 0xb7, 0x63, 0xc8, 0x62, 0xd9, 0x61,
    0xea, 0x60, 0x39, 0xf1, 0x87, 0x21, 0xa7, 0x01, 0xb7, 0x20,
    0x39, 0xf1, 0x5f, 0x38, 0x6d, 0xc1, 0xaf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea7__data[] = {
    0x90, 0x11,
    0x0f, 0x26, 0xfe, 0x10, 0x2a, 0x93, 0x87, 0x17, 0xa3, 0x14,
    0xb2, 0x42, 0x0a, 0x92, 0x19, 0x40, 0x36, 0x14, 0x50, 0x41,
    0x82, 0x16, 0x2b, 0x93, 0x24, 0x41, 0xbb, 0x14, 0xb8, 0x00,
    0xc2, 0x43, 0xc3, 0x13, 0x1b, 0x94, 0x67, 0x12, 0xc4, 0x15,
    0x53, 0xc1, 0xd2, 0x41, 0x12, 0xc1, 0x29, 0x13, 0x85, 0x17,
    0x1b, 0x92, 0x1a, 0x42, 0x47, 0x13, 0x83, 0x41, 0xa7, 0x13,
    0x0e, 0x91, 0xa7, 0x63, 0xb7, 0x63, 0xc5, 0x65, 0xd5, 0x65,
    0xdd, 0x4a, 0xe3, 0x67, 0xf3, 0x67, 0x8d, 0xc1, 0xae, 0x42,
    0xdf, 0x20,
    0xfd
};

static const uint8_t L_GroundArea8__data[] = {
    0x90, 0x11,
    0x0f, 0x26, 0x6e, 0x10, 0x8b, 0x17, 0xaf, 0x32, 0xd8, 0x62,
    0xe8, 0x62, 0xfc, 0x3f, 0xad, 0xc8, 0xf8, 0x64, 0x0c, 0xbe,
    0x43, 0x43, 0xf8, 0x64, 0x0c, 0xbf, 0x73, 0x40, 0x84, 0x40,
    0x93, 0x40, 0xa4, 0x40, 0xb3, 0x40, 0xf8, 0x64, 0x48, 0xe4,
    0x5c, 0x39, 0x83, 0x40, 0x92, 0x41, 0xb3, 0x40, 0xf8, 0x64,
    0x48, 0xe4, 0x5c, 0x39, 0xf8, 0x64, 0x13, 0xc2, 0x37, 0x65,
    0x4c, 0x24, 0x63, 0x00, 0x97, 0x65, 0xc3, 0x42, 0x0b, 0x97,
    0xac, 0x32, 0xf8, 0x64, 0x0c, 0xbe, 0x53, 0x45, 0x9d, 0x48,
    0xf8, 0x64, 0x2a, 0xe2, 0x3c, 0x47, 0x56, 0x43, 0xba, 0x62,
    0xf8, 0x64, 0x0c, 0xb7, 0x88, 0x64, 0xbc, 0x31, 0xd4, 0x45,
    0xfc, 0x31, 0x3c, 0xb1, 0x78, 0x64, 0x8c, 0x38, 0x0b, 0x9c,
    0x1a, 0x33, 0x18, 0x61, 0x28, 0x61, 0x39, 0x60, 0x5d, 0x4a,
    0xee, 0x11, 0x0f, 0xb8, 0x1d, 0xc1, 0x3e, 0x42, 0x6f, 0x20,
    0xfd
};

static const uint8_t L_GroundArea9__data[] = {
    0x52, 0x31,
    0x0f, 0x20, 0x6e, 0x40, 0xf7, 0x20, 0x07, 0x84, 0x17, 0x20,
    0x4f, 0x34, 0xc3, 0x03, 0xc7, 0x02, 0xd3, 0x22, 0x27, 0xe3,
    0x39, 0x61, 0xe7, 0x73, 0x5c, 0xe4, 0x57, 0x00, 0x6c, 0x73,
    0x47, 0xa0, 0x53, 0x06, 0x63, 0x22, 0xa7, 0x73, 0xfc, 0x73,
    0x13, 0xa1, 0x33, 0x05, 0x43, 0x21, 0x5c, 0x72, 0xc3, 0x23,
    0xcc, 0x03, 0x77, 0xfb, 0xac, 0x02, 0x39, 0xf1, 0xa7, 0x73,
    0xd3, 0x04, 0xe8, 0x72, 0xe3, 0x22, 0x26, 0xf4, 0xbc, 0x02,
    0x8c, 0x81, 0xa8, 0x62, 0x17, 0x87, 0x43, 0x24, 0xa7, 0x01,
    0xc3, 0x04, 0x08, 0xf2, 0x97, 0x21, 0xa3, 0x02, 0xc9, 0x0b,
    0xe1, 0x69, 0xf1, 0x69, 0x8d, 0xc1, 0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea10__data[] = {
    0x38, 0x11,
    0x0f, 0x26, 0xad, 0x40, 0x3d, 0xc7,
    0xfd
};

static const uint8_t L_GroundArea11__data[] = {
    0x95, 0xb1,
    0x0f, 0x26, 0x0d, 0x02, 0xc8, 0x72, 0x1c, 0x81, 0x38, 0x72,
    0x0d, 0x05, 0x97, 0x34, 0x98, 0x62, 0xa3, 0x20, 0xb3, 0x06,
    0xc3, 0x20, 0xcc, 0x03, 0xf9, 0x91, 0x2c, 0x81, 0x48, 0x62,
    0x0d, 0x09, 0x37, 0x63, 0x47, 0x03, 0x57, 0x21, 0x8c, 0x02,
    0xc5, 0x79, 0xc7, 0x31, 0xf9, 0x11, 0x39, 0xf1, 0xa9, 0x11,
    0x6f, 0xb4, 0xd3, 0x65, 0xe3, 0x65, 0x7d, 0xc1, 0xbf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea12__data[] = {
    0x00, 0xc1,
    0x4c, 0x00, 0xf4, 0x4f, 0x0d, 0x02, 0x02, 0x42, 0x43, 0x4f,
    0x52, 0xc2, 0xde, 0x00, 0x5a, 0xc2, 0x4d, 0xc7,
    0xfd
};

static const uint8_t L_GroundArea13__data[] = {
    0x90, 0x51,
    0x0f, 0x26, 0xee, 0x10, 0x0b, 0x94, 0x33, 0x14, 0x42, 0x42,
    0x77, 0x16, 0x86, 0x44, 0x02, 0x92, 0x4a, 0x16, 0x69, 0x42,
    0x73, 0x14, 0xb0, 0x00, 0xc7, 0x12, 0x05, 0xc0, 0x1c, 0x17,
    0x1f, 0x11, 0x36, 0x12, 0x8f, 0x14, 0x91, 0x40, 0x1b, 0x94,
    0x35, 0x12, 0x34, 0x42, 0x60, 0x42, 0x61, 0x12, 0x87, 0x12,
    0x96, 0x40, 0xa3, 0x14, 0x1c, 0x98, 0x1f, 0x11, 0x47, 0x12,
    0x9f, 0x15, 0xcc, 0x15, 0xcf, 0x11, 0x05, 0xc0, 0x1f, 0x15,
    0x39, 0x12, 0x7c, 0x16, 0x7f, 0x11, 0x82, 0x40, 0x98, 0x12,
    0xdf, 0x15, 0x16, 0xc4, 0x17, 0x14, 0x54, 0x12, 0x9b, 0x16,
    0x28, 0x94, 0xce, 0x01, 0x3d, 0xc1, 0x5e, 0x42, 0x8f, 0x20,
    0xfd
};

static const uint8_t L_GroundArea14__data[] = {
    0x97, 0x11,
    0x0f, 0x26, 0xfe, 0x10, 0x2b, 0x92, 0x57, 0x12, 0x8b, 0x12,
    0xc0, 0x41, 0xf7, 0x13, 0x5b, 0x92, 0x69, 0x0b, 0xbb, 0x12,
    0xb2, 0x46, 0x19, 0x93, 0x71, 0x00, 0x17, 0x94, 0x7c, 0x14,
    0x7f, 0x11, 0x93, 0x41, 0xbf, 0x15, 0xfc, 0x13, 0xff, 0x11,
    0x2f, 0x95, 0x50, 0x42, 0x51, 0x12, 0x58, 0x14, 0xa6, 0x12,
    0xdb, 0x12, 0x1b, 0x93, 0x46, 0x43, 0x7b, 0x12, 0x8d, 0x49,
    0xb7, 0x14, 0x1b, 0x94, 0x49, 0x0b, 0xbb, 0x12, 0xfc, 0x13,
    0xff, 0x12, 0x03, 0xc1, 0x2f, 0x15, 0x43, 0x12, 0x4b, 0x13,
    0x77, 0x13, 0x9d, 0x4a, 0x15, 0xc1, 0xa1, 0x41, 0xc3, 0x12,
    0xfe, 0x01, 0x7d, 0xc1, 0x9e, 0x42, 0xcf, 0x20,
    0xfd
};

static const uint8_t L_GroundArea15__data[] = {
    0x52, 0x21,
    0x0f, 0x20, 0x6e, 0x44, 0x0c, 0xf1, 0x4c, 0x01, 0xaa, 0x35,
    0xd9, 0x34, 0xee, 0x20, 0x08, 0xb3, 0x37, 0x32, 0x43, 0x04,
    0x4e, 0x21, 0x53, 0x20, 0x7c, 0x01, 0x97, 0x21, 0xb7, 0x07,
    0x9c, 0x81, 0xe7, 0x42, 0x5f, 0xb3, 0x97, 0x63, 0xac, 0x02,
    0xc5, 0x41, 0x49, 0xe0, 0x58, 0x61, 0x76, 0x64, 0x85, 0x65,
    0x94, 0x66, 0xa4, 0x22, 0xa6, 0x03, 0xc8, 0x22, 0xdc, 0x02,
    0x68, 0xf2, 0x96, 0x42, 0x13, 0x82, 0x17, 0x02, 0xaf, 0x34,
    0xf6, 0x21, 0xfc, 0x06, 0x26, 0x80, 0x2a, 0x24, 0x36, 0x01,
    0x8c, 0x00, 0xff, 0x35, 0x4e, 0xa0, 0x55, 0x21, 0x77, 0x20,
    0x87, 0x07, 0x89, 0x22, 0xae, 0x21, 0x4c, 0x82, 0x9f, 0x34,
    0xec, 0x01, 0x03, 0xe7, 0x13, 0x67, 0x8d, 0x4a, 0xad, 0x41,
    0x0f, 0xa6,
    0xfd
};

static const uint8_t L_GroundArea16__data[] = {
    0x10, 0x51,
    0x4c, 0x00, 0xc7, 0x12, 0xc6, 0x42, 0x03, 0x92, 0x02, 0x42,
    0x29, 0x12, 0x63, 0x12, 0x62, 0x42, 0x69, 0x14, 0xa5, 0x12,
    0xa4, 0x42, 0xe2, 0x14, 0xe1, 0x44, 0xf8, 0x16, 0x37, 0xc1,
    0x8f, 0x38, 0x02, 0xbb, 0x28, 0x7a, 0x68, 0x7a, 0xa8, 0x7a,
    0xe0, 0x6a, 0xf0, 0x6a, 0x6d, 0xc5,
    0xfd
};

static const uint8_t L_GroundArea17__data[] = {
    0x92, 0x31,
    0x0f, 0x20, 0x6e, 0x40, 0x0d, 0x02, 0x37, 0x73, 0xec, 0x00,
    0x0c, 0x80, 0x3c, 0x00, 0x6c, 0x00, 0x9c, 0x00, 0x06, 0xc0,
    0xc7, 0x73, 0x06, 0x83, 0x28, 0x72, 0x96, 0x40, 0xe7, 0x73,
    0x26, 0xc0, 0x87, 0x7b, 0xd2, 0x41, 0x39, 0xf1, 0xc8, 0xf2,
    0x97, 0xe3, 0xa3, 0x23, 0xe7, 0x02, 0xe3, 0x07, 0xf3, 0x22,
    0x37, 0xe3, 0x9c, 0x00, 0xbc, 0x00, 0xec, 0x00, 0x0c, 0x80,
    0x3c, 0x00, 0x86, 0x21, 0xa6, 0x06, 0xb6, 0x24, 0x5c, 0x80,
    0x7c, 0x00, 0x9c, 0x00, 0x29, 0xe1, 0xdc, 0x05, 0xf6, 0x41,
    0xdc, 0x80, 0xe8, 0x72, 0x0c, 0x81, 0x27, 0x73, 0x4c, 0x01,
    0x66, 0x74, 0x0d, 0x11, 0x3f, 0x35, 0xb6, 0x41, 0x2c, 0x82,
    0x36, 0x40, 0x7c, 0x02, 0x86, 0x40, 0xf9, 0x61, 0x39, 0xe1,
    0xac, 0x04, 0xc6, 0x41, 0x0c, 0x83, 0x16, 0x41, 0x88, 0xf2,
    0x39, 0xf1, 0x7c, 0x00, 0x89, 0x61, 0x9c, 0x00, 0xa7, 0x63,
    0xbc, 0x00, 0xc5, 0x65, 0xdc, 0x00, 0xe3, 0x67, 0xf3, 0x67,
    0x8d, 0xc1, 0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea18__data[] = {
    0x55, 0xb1,
    0x0f, 0x26, 0xcf, 0x33, 0x07, 0xb2, 0x15, 0x11, 0x52, 0x42,
    0x99, 0x0b, 0xac, 0x02, 0xd3, 0x24, 0xd6, 0x42, 0xd7, 0x25,
    0x23, 0x84, 0xcf, 0x33, 0x07, 0xe3, 0x19, 0x61, 0x78, 0x7a,
    0xef, 0x33, 0x2c, 0x81, 0x46, 0x64, 0x55, 0x65, 0x65, 0x65,
    0xec, 0x74, 0x47, 0x82, 0x53, 0x05, 0x63, 0x21, 0x62, 0x41,
    0x96, 0x22, 0x9a, 0x41, 0xcc, 0x03, 0xb9, 0x91, 0x39, 0xf1,
    0x63, 0x26, 0x67, 0x27, 0xd3, 0x06, 0xfc, 0x01, 0x18, 0xe2,
    0xd9, 0x07, 0xe9, 0x04, 0x0c, 0x86, 0x37, 0x22, 0x93, 0x24,
    0x87, 0x84, 0xac, 0x02, 0xc2, 0x41, 0xc3, 0x23, 0xd9, 0x71,
    0xfc, 0x01, 0x7f, 0xb1, 0x9c, 0x00, 0xa7, 0x63, 0xb6, 0x64,
    0xcc, 0x00, 0xd4, 0x66, 0xe3, 0x67, 0xf3, 0x67, 0x8d, 0xc1,
    0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea19__data[] = {
    0x50, 0xb1,
    0x0f, 0x26, 0xfc, 0x00, 0x1f, 0xb3, 0x5c, 0x00, 0x65, 0x65,
    0x74, 0x66, 0x83, 0x67, 0x93, 0x67, 0xdc, 0x73, 0x4c, 0x80,
    0xb3, 0x20, 0xc9, 0x0b, 0xc3, 0x08, 0xd3, 0x2f, 0xdc, 0x00,
    0x2c, 0x80, 0x4c, 0x00, 0x8c, 0x00, 0xd3, 0x2e, 0xed, 0x4a,
    0xfc, 0x00, 0xd7, 0xa1, 0xec, 0x01, 0x4c, 0x80, 0x59, 0x11,
    0xd8, 0x11, 0xda, 0x10, 0x37, 0xa0, 0x47, 0x04, 0x99, 0x11,
    0xe7, 0x21, 0x3a, 0x90, 0x67, 0x20, 0x76, 0x10, 0x77, 0x60,
    0x87, 0x07, 0xd8, 0x12, 0x39, 0xf1, 0xac, 0x00, 0xe9, 0x71,
    0x0c, 0x80, 0x2c, 0x00, 0x4c, 0x05, 0xc7, 0x7b, 0x39, 0xf1,
    0xec, 0x00, 0xf9, 0x11, 0x0c, 0x82, 0x6f, 0x34, 0xf8, 0x11,
    0xfa, 0x10, 0x7f, 0xb2, 0xac, 0x00, 0xb6, 0x64, 0xcc, 0x01,
    0xe3, 0x67, 0xf3, 0x67, 0x8d, 0xc1, 0xcf, 0x26,
    0xfd
};

static const uint8_t L_GroundArea20__data[] = {
    0x52, 0xb1,
    0x0f, 0x20, 0x6e, 0x45, 0x39, 0x91, 0xb3, 0x04, 0xc3, 0x21,
    0xc8, 0x11, 0xca, 0x10, 0x49, 0x91, 0x7c, 0x73, 0xe8, 0x12,
    0x88, 0x91, 0x8a, 0x10, 0xe7, 0x21, 0x05, 0x91, 0x07, 0x30,
    0x17, 0x07, 0x27, 0x20, 0x49, 0x11, 0x9c, 0x01, 0xc8, 0x72,
    0x23, 0xa6, 0x27, 0x26, 0xd3, 0x03, 0xd8, 0x7a, 0x89, 0x91,
    0xd8, 0x72, 0x39, 0xf1, 0xa9, 0x11, 0x09, 0xf1, 0x63, 0x24,
    0x67, 0x24, 0xd8, 0x62, 0x28, 0x91, 0x2a, 0x10, 0x56, 0x21,
    0x70, 0x04, 0x79, 0x0b, 0x8c, 0x00, 0x94, 0x21, 0x9f, 0x35,
    0x2f, 0xb8, 0x3d, 0xc1, 0x7f, 0x26,
    0xfd
};

static const uint8_t L_GroundArea21__data[] = {
    0x06, 0xc1,
    0x4c, 0x00, 0xf4, 0x4f, 0x0d, 0x02, 0x06, 0x20, 0x24, 0x4f,
    0x35, 0xa0, 0x36, 0x20, 0x53, 0x46, 0xd5, 0x20, 0xd6, 0x20,
    0x34, 0xa1, 0x73, 0x49, 0x74, 0x20, 0x94, 0x20, 0xb4, 0x20,
    0xd4, 0x20, 0xf4, 0x20, 0x2e, 0x80, 0x59, 0x42, 0x4d, 0xc7,
    0xfd
};

static const uint8_t L_GroundArea22__data[] = {
    0x96, 0x31,
    0x0f, 0x26, 0x0d, 0x03, 0x1a, 0x60, 0x77, 0x42, 0xc4, 0x00,
    0xc8, 0x62, 0xb9, 0xe1, 0xd3, 0x06, 0xd7, 0x07, 0xf9, 0x61,
    0x0c, 0x81, 0x4e, 0xb1, 0x8e, 0xb1, 0xbc, 0x01, 0xe4, 0x50,
    0xe9, 0x61, 0x0c, 0x81, 0x0d, 0x0a, 0x84, 0x43, 0x98, 0x72,
    0x0d, 0x0c, 0x0f, 0x38, 0x1d, 0xc1, 0x5f, 0x26,
    0xfd
};

static const uint8_t L_UndergroundArea1__data[] = {
    0x48, 0x0f,
    0x0e, 0x01, 0x5e, 0x02, 0xa7, 0x00, 0xbc, 0x73, 0x1a, 0xe0,
    0x39, 0x61, 0x58, 0x62, 0x77, 0x63, 0x97, 0x63, 0xb8, 0x62,
    0xd6, 0x07, 0xf8, 0x62, 0x19, 0xe1, 0x75, 0x52, 0x86, 0x40,
    0x87, 0x50, 0x95, 0x52, 0x93, 0x43, 0xa5, 0x21, 0xc5, 0x52,
    0xd6, 0x40, 0xd7, 0x20, 0xe5, 0x06, 0xe6, 0x51, 0x3e, 0x8d,
    0x5e, 0x03, 0x67, 0x52, 0x77, 0x52, 0x7e, 0x02, 0x9e, 0x03,
    0xa6, 0x43, 0xa7, 0x23, 0xde, 0x05, 0xfe, 0x02, 0x1e, 0x83,
    0x33, 0x54, 0x46, 0x40, 0x47, 0x21, 0x56, 0x04, 0x5e, 0x02,
    0x83, 0x54, 0x93, 0x52, 0x96, 0x07, 0x97, 0x50, 0xbe, 0x03,
    0xc7, 0x23, 0xfe, 0x02, 0x0c, 0x82, 0x43, 0x45, 0x45, 0x24,
    0x46, 0x24, 0x90, 0x08, 0x95, 0x51, 0x78, 0xfa, 0xd7, 0x73,
    0x39, 0xf1, 0x8c, 0x01, 0xa8, 0x52, 0xb8, 0x52, 0xcc, 0x01,
    0x5f, 0xb3, 0x97, 0x63, 0x9e, 0x00, 0x0e, 0x81, 0x16, 0x24,
    0x66, 0x04, 0x8e, 0x00, 0xfe, 0x01, 0x08, 0xd2, 0x0e, 0x06,
    0x6f, 0x47, 0x9e, 0x0f, 0x0e, 0x82, 0x2d, 0x47, 0x28, 0x7a,
    0x68, 0x7a, 0xa8, 0x7a, 0xae, 0x01, 0xde, 0x0f, 0x6d, 0xc5,
    0xfd
};

static const uint8_t L_UndergroundArea2__data[] = {
    0x48, 0x0f,
    0x0e, 0x01, 0x5e, 0x02, 0xbc, 0x01, 0xfc, 0x01, 0x2c, 0x82,
    0x41, 0x52, 0x4e, 0x04, 0x67, 0x25, 0x68, 0x24, 0x69, 0x24,
    0xba, 0x42, 0xc7, 0x04, 0xde, 0x0b, 0xb2, 0x87, 0xfe, 0x02,
    0x2c, 0xe1, 0x2c, 0x71, 0x67, 0x01, 0x77, 0x00, 0x87, 0x01,
    0x8e, 0x00, 0xee, 0x01, 0xf6, 0x02, 0x03, 0x85, 0x05, 0x02,
    0x13, 0x21, 0x16, 0x02, 0x27, 0x02, 0x2e, 0x02, 0x88, 0x72,
    0xc7, 0x20, 0xd7, 0x07, 0xe4, 0x76, 0x07, 0xa0, 0x17, 0x06,
    0x48, 0x7a, 0x76, 0x20, 0x98, 0x72, 0x79, 0xe1, 0x88, 0x62,
    0x9c, 0x01, 0xb7, 0x73, 0xdc, 0x01, 0xf8, 0x62, 0xfe, 0x01,
    0x08, 0xe2, 0x0e, 0x00, 0x6e, 0x02, 0x73, 0x20, 0x77, 0x23,
    0x83, 0x04, 0x93, 0x20, 0xae, 0x00, 0xfe, 0x0a, 0x0e, 0x82,
    0x39, 0x71, 0xa8, 0x72, 0xe7, 0x73, 0x0c, 0x81, 0x8f, 0x32,
    0xae, 0x00, 0xfe, 0x04, 0x04, 0xd1, 0x17, 0x04, 0x26, 0x49,
    0x27, 0x29, 0xdf, 0x33, 0xfe, 0x02, 0x44, 0xf6, 0x7c, 0x01,
    0x8e, 0x06, 0xbf, 0x47, 0xee, 0x0f, 0x4d, 0xc7, 0x0e, 0x82,
    0x68, 0x7a, 0xae, 0x01, 0xde, 0x0f, 0x6d, 0xc5,
    0xfd
};

static const uint8_t L_UndergroundArea3__data[] = {
    0x48, 0x01,
    0x0e, 0x01, 0x00, 0x5a, 0x3e, 0x06, 0x45, 0x46, 0x47, 0x46,
    0x53, 0x44, 0xae, 0x01, 0xdf, 0x4a, 0x4d, 0xc7, 0x0e, 0x81,
    0x00, 0x5a, 0x2e, 0x04, 0x37, 0x28, 0x3a, 0x48, 0x46, 0x47,
    0xc7, 0x07, 0xce, 0x0f, 0xdf, 0x4a, 0x4d, 0xc7, 0x0e, 0x81,
    0x00, 0x5a, 0x33, 0x53, 0x43, 0x51, 0x46, 0x40, 0x47, 0x50,
    0x53, 0x04, 0x55, 0x40, 0x56, 0x50, 0x62, 0x43, 0x64, 0x40,
    0x65, 0x50, 0x71, 0x41, 0x73, 0x51, 0x83, 0x51, 0x94, 0x40,
    0x95, 0x50, 0xa3, 0x50, 0xa5, 0x40, 0xa6, 0x50, 0xb3, 0x51,
    0xb6, 0x40, 0xb7, 0x50, 0xc3, 0x53, 0xdf, 0x4a, 0x4d, 0xc7,
    0x0e, 0x81, 0x00, 0x5a, 0x2e, 0x02, 0x36, 0x47, 0x37, 0x52,
    0x3a, 0x49, 0x47, 0x25, 0xa7, 0x52, 0xd7, 0x04, 0xdf, 0x4a,
    0x4d, 0xc7, 0x0e, 0x81, 0x00, 0x5a, 0x3e, 0x02, 0x44, 0x51,
    0x53, 0x44, 0x54, 0x44, 0x55, 0x24, 0xa1, 0x54, 0xae, 0x01,
    0xb4, 0x21, 0xdf, 0x4a, 0xe5, 0x07, 0x4d, 0xc7,
    0xfd
};

static const uint8_t L_WaterArea1__data[] = {
    0x41, 0x01,
    0xb4, 0x34, 0xc8, 0x52, 0xf2, 0x51, 0x47, 0xd3, 0x6c, 0x03,
    0x65, 0x49, 0x9e, 0x07, 0xbe, 0x01, 0xcc, 0x03, 0xfe, 0x07,
    0x0d, 0xc9, 0x1e, 0x01, 0x6c, 0x01, 0x62, 0x35, 0x63, 0x53,
    0x8a, 0x41, 0xac, 0x01, 0xb3, 0x53, 0xe9, 0x51, 0x26, 0xc3,
    0x27, 0x33, 0x63, 0x43, 0x64, 0x33, 0xba, 0x60, 0xc9, 0x61,
    0xce, 0x0b, 0xe5, 0x09, 0xee, 0x0f, 0x7d, 0xca, 0x7d, 0x47,
    0xfd
};

static const uint8_t L_WaterArea2__data[] = {
    0x41, 0x01,
    0xb8, 0x52, 0xea, 0x41, 0x27, 0xb2, 0xb3, 0x42, 0x16, 0xd4,
    0x4a, 0x42, 0xa5, 0x51, 0xa7, 0x31, 0x27, 0xd3, 0x08, 0xe2,
    0x16, 0x64, 0x2c, 0x04, 0x38, 0x42, 0x76, 0x64, 0x88, 0x62,
    0xde, 0x07, 0xfe, 0x01, 0x0d, 0xc9, 0x23, 0x32, 0x31, 0x51,
    0x98, 0x52, 0x0d, 0xc9, 0x59, 0x42, 0x63, 0x53, 0x67, 0x31,
    0x14, 0xc2, 0x36, 0x31, 0x87, 0x53, 0x17, 0xe3, 0x29, 0x61,
    0x30, 0x62, 0x3c, 0x08, 0x42, 0x37, 0x59, 0x40, 0x6a, 0x42,
    0x99, 0x40, 0xc9, 0x61, 0xd7, 0x63, 0x39, 0xd1, 0x58, 0x52,
    0xc3, 0x67, 0xd3, 0x31, 0xdc, 0x06, 0xf7, 0x42, 0xfa, 0x42,
    0x23, 0xb1, 0x43, 0x67, 0xc3, 0x34, 0xc7, 0x34, 0xd1, 0x51,
    0x43, 0xb3, 0x47, 0x33, 0x9a, 0x30, 0xa9, 0x61, 0xb8, 0x62,
    0xbe, 0x0b, 0xd5, 0x09, 0xde, 0x0f, 0x0d, 0xca, 0x7d, 0x47,
    0xfd
};

static const uint8_t L_WaterArea3__data[] = {
    0x49, 0x0f,
    0x1e, 0x01, 0x39, 0x73, 0x5e, 0x07, 0xae, 0x0b, 0x1e, 0x82,
    0x6e, 0x88, 0x9e, 0x02, 0x0d, 0x04, 0x2e, 0x0b, 0x45, 0x09,
    0x4e, 0x0f, 0xed, 0x47,
    0xfd,
    0xff
};

static const uint8_t X_SubtracterData__data[] = {
    0x00, 0x10
};

static const uint8_t OffscrJoypadBitsData__data[] = {
    0x01, 0x02
};

static const uint8_t Hidden1UpCoinAmts__data[] = {
    0x15, 0x23, 0x16, 0x1b, 0x17, 0x18, 0x23, 0x63
};

static const uint8_t ClimbAdderLow__data[] = {
    0x0e, 0x04, 0xfc, 0xf2
};

static const uint8_t ClimbAdderHigh__data[] = {
    0x00, 0x00, 0xff, 0xff
};

static const uint8_t JumpMForceData__data[] = {
    0x20, 0x20, 0x1e, 0x28, 0x28, 0x0d, 0x04
};

static const uint8_t FallMForceData__data[] = {
    0x70, 0x70, 0x60, 0x90, 0x90, 0x0a, 0x09
};

static const uint8_t PlayerYSpdData__data[] = {
    0xfc, 0xfc, 0xfc, 0xfb, 0xfb, 0xfe, 0xff
};

static const uint8_t InitMForceData__data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00
};

static const uint8_t MaxLeftXSpdData__data[] = {
    0xd8, 0xe8, 0xf0
};

static const uint8_t MaxRightXSpdData__data[] = {
    0x28, 0x18, 0x10,
    0x0c
};

static const uint8_t FrictionData__data[] = {
    0xe4, 0x98, 0xd0
};

static const uint8_t Climb_Y_SpeedData__data[] = {
    0x00, 0xff, 0x01
};

static const uint8_t Climb_Y_MForceData__data[] = {
    0x00, 0x20, 0xff
};

static const uint8_t PlayerAnimTmrData__data[] = {
    0x02, 0x04, 0x07
};

static const uint8_t FireballXSpdData__data[] = {
    0x40, 0xc0
};

static const uint8_t Bubble_MForceData__data[] = {
    0xff, 0x50
};

static const uint8_t BubbleTimerData__data[] = {
    0x40, 0x20
};

static const uint8_t FlagpoleScoreMods__data[] = {
    0x05, 0x02, 0x08, 0x04, 0x01
};

static const uint8_t FlagpoleScoreDigits__data[] = {
    0x03, 0x03, 0x04, 0x04, 0x04
};

static const uint8_t Jumpspring_Y_PosData__data[] = {
    0x08, 0x10, 0x08, 0x00
};

static const uint8_t VineHeightData__data[] = {
    0x30, 0x60
};

static const uint8_t CannonBitmasks__data[] = {
    BOOST_BINARY(00001111), BOOST_BINARY(00000111)
};

static const uint8_t BulletBillXSpdData__data[] = {
    0x18, 0xe8
};

static const uint8_t HammerEnemyOfsData__data[] = {
    0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
    0x06, 0x06, 0x06
};

static const uint8_t HammerXSpdData__data[] = {
    0x10, 0xf0
};

static const uint8_t CoinTallyOffsets__data[] = {
    0x17, 0x1d
};

static const uint8_t ScoreOffsets__data[] = {
    0x0b, 0x11
};

static const uint8_t StatusBarNybbles__data[] = {
    0x02, 0x13
};

static const uint8_t BlockYPosAdderData__data[] = {
    0x04, 0x12
};

static const uint8_t BrickQBlockMetatiles__data[] = {
    0xc1, 0xc0, 0x5f, 0x60,
    0x55, 0x56, 0x57, 0x58, 0x59,
    0x5a, 0x5b, 0x5c, 0x5d, 0x5e
};

static const uint8_t MaxSpdBlockData__data[] = {
    0x06, 0x08
};

static const uint8_t LoopCmdWorldNumber__data[] = {
    0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07
};

static const uint8_t LoopCmdPageNumber__data[] = {
    0x05, 0x09, 0x04, 0x05, 0x06, 0x08, 0x09, 0x0a, 0x06, 0x0b, 0x10
};

static const uint8_t LoopCmdYPosition__data[] = {
    0x40, 0xb0, 0xb0, 0x80, 0x40, 0x40, 0x80, 0x40, 0xf0, 0xf0, 0xf0
};

static const uint8_t NormalXSpdData__data[] = {
    0xf8, 0xf4
};

static const uint8_t HBroWalkingTimerData__data[] = {
    0x80, 0x50
};

static const uint8_t PRDiffAdjustData__data[] = {
    0x26, 0x2c, 0x32, 0x38,
    0x20, 0x22, 0x24, 0x26,
    0x13, 0x14, 0x15, 0x16
};

static const uint8_t FirebarSpinSpdData__data[] = {
    0x28, 0x38, 0x28, 0x38, 0x28
};

static const uint8_t FirebarSpinDirData__data[] = {
    0x00, 0x00, 0x10, 0x10, 0x00
};

static const uint8_t FlyCCXPositionData__data[] = {
    0x80, 0x30, 0x40, 0x80,
    0x30, 0x50, 0x50, 0x70,
    0x20, 0x40, 0x80, 0xa0,
    0x70, 0x40, 0x90, 0x68
};

static const uint8_t FlyCCXSpeedData__data[] = {
    0x0e, 0x05, 0x06, 0x0e,
    0x1c, 0x20, 0x10, 0x0c,
    0x1e, 0x22, 0x18, 0x14
};

static const uint8_t FlyCCTimerData__data[] = {
    0x10, 0x60, 0x20, 0x48
};

static const uint8_t FlameYPosData__data[] = {
    0x90, 0x80, 0x70, 0x90
};

static const uint8_t FlameYMFAdderData__data[] = {
    0xff, 0x01
};

static const uint8_t FireworksXPosData__data[] = {
    0x00, 0x30, 0x60, 0x60, 0x00, 0x20
};

static const uint8_t FireworksYPosData__data[] = {
    0x60, 0x40, 0x70, 0x40, 0x60, 0x30
};

static const uint8_t Bitmasks__data[] = {
    BOOST_BINARY(00000001), BOOST_BINARY(00000010), BOOST_BINARY(00000100), BOOST_BINARY(00001000), BOOST_BINARY(00010000), BOOST_BINARY(00100000), BOOST_BINARY(01000000), BOOST_BINARY(10000000)
};

static const uint8_t Enemy17YPosData__data[] = {
    0x40, 0x30, 0x90, 0x50, 0x20, 0x60, 0xa0, 0x70
};

static const uint8_t SwimCC_IDData__data[] = {
    0x0a, 0x0b
};

static const uint8_t PlatPosDataLow__data[] = {
    0x08, 0x0c, 0xf8
};

static const uint8_t PlatPosDataHigh__data[] = {
    0x00, 0x00, 0xff
};

static const uint8_t HammerThrowTmrData__data[] = {
    0x30, 0x1c
};

static const uint8_t XSpeedAdderData__data[] = {
    0x00, 0xe8, 0x00, 0x18
};

static const uint8_t RevivedXSpeed__data[] = {
    0x08, 0xf8, 0x0c, 0xf4
};

static const uint8_t HammerBroJumpLData__data[] = {
    0x20, 0x37
};

static const uint8_t BlooberBitmasks__data[] = {
    BOOST_BINARY(00111111), BOOST_BINARY(00000011)
};

static const uint8_t SwimCCXMoveData__data[] = {
    0x40, 0x80,
    0x04, 0x04
};

static const uint8_t FirebarPosLookupTbl__data[] = {
    0x00, 0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0x07, 0x08,
    0x00, 0x03, 0x06, 0x09, 0x0b, 0x0d, 0x0e, 0x0f, 0x10,
    0x00, 0x04, 0x09, 0x0d, 0x10, 0x13, 0x16, 0x17, 0x18,
    0x00, 0x06, 0x0c, 0x12, 0x16, 0x1a, 0x1d, 0x1f, 0x20,
    0x00, 0x07, 0x0f, 0x16, 0x1c, 0x21, 0x25, 0x27, 0x28,
    0x00, 0x09, 0x12, 0x1b, 0x21, 0x27, 0x2c, 0x2f, 0x30,
    0x00, 0x0b, 0x15, 0x1f, 0x27, 0x2e, 0x33, 0x37, 0x38,
    0x00, 0x0c, 0x18, 0x24, 0x2d, 0x35, 0x3b, 0x3e, 0x40,
    0x00, 0x0e, 0x1b, 0x28, 0x32, 0x3b, 0x42, 0x46, 0x48,
    0x00, 0x0f, 0x1f, 0x2d, 0x38, 0x42, 0x4a, 0x4e, 0x50,
    0x00, 0x11, 0x22, 0x31, 0x3e, 0x49, 0x51, 0x56, 0x58
};

static const uint8_t FirebarMirrorData__data[] = {
    0x01, 0x03, 0x02, 0x00
};

static const uint8_t FirebarTblOffsets__data[] = {
    0x00, 0x09, 0x12, 0x1b, 0x24, 0x2d,
    0x36, 0x3f, 0x48, 0x51, 0x5a, 0x63
};

static const uint8_t FirebarYPos__data[] = {
    0x0c, 0x18
};

static const uint8_t PRandomSubtracter__data[] = {
    0xf8, 0xa0, 0x70, 0xbd, 0x00
};

static const uint8_t FlyCCBPriority__data[] = {
    0x20, 0x20, 0x20, 0x00, 0x00
};

static const uint8_t LakituDiffAdj__data[] = {
    0x15, 0x30, 0x40
};

static const uint8_t BridgeCollapseData__data[] = {
    0x1a,
    0x58,
    0x98, 0x96, 0x94, 0x92, 0x90, 0x8e, 0x8c,
    0x8a, 0x88, 0x86, 0x84, 0x82, 0x80
};

static const uint8_t PRandomRange__data[] = {
    0x21, 0x41, 0x11, 0x31
};

static const uint8_t FlameTimerData__data[] = {
    0xbf, 0x40, 0xbf, 0xbf, 0xbf, 0x40, 0x40, 0xbf
};

static const uint8_t StarFlagYPosAdder__data[] = {
    0x00, 0x00, 0x08, 0x08
};

static const uint8_t StarFlagXPosAdder__data[] = {
    0x00, 0x08, 0x00, 0x08
};

static const uint8_t StarFlagTileData__data[] = {
    0x54, 0x55, 0x56, 0x57
};

static const uint8_t BowserIdentities__data[] = {
    Goomba, GreenKoopa, BuzzyBeetle, Spiny, Lakitu, Bloober, HammerBro, Bowser
};

static const uint8_t ResidualXSpdData__data[] = {
    0x18, 0xe8
};

static const uint8_t KickedShellXSpdData__data[] = {
    0x30, 0xd0
};

static const uint8_t DemotedKoopaXSpdData__data[] = {
    0x08, 0xf8
};

static const uint8_t KickedShellPtsData__data[] = {
    0x0a, 0x06, 0x04
};

static const uint8_t StompedEnemyPtsData__data[] = {
    0x02, 0x06, 0x05, 0x06
};

static const uint8_t RevivalRateData__data[] = {
    0x10, 0x0b
};

static const uint8_t SetBitsMask__data[] = {
    BOOST_BINARY(10000000), BOOST_BINARY(01000000), BOOST_BINARY(00100000), BOOST_BINARY(00010000), BOOST_BINARY(00001000), BOOST_BINARY(00000100), BOOST_BINARY(00000010)
};

static const uint8_t ClearBitsMask__data[] = {
    BOOST_BINARY(01111111), BOOST_BINARY(10111111), BOOST_BINARY(11011111), BOOST_BINARY(11101111), BOOST_BINARY(11110111), BOOST_BINARY(11111011), BOOST_BINARY(11111101)
};

static const uint8_t PlayerPosSPlatData__data[] = {
    0x80, 0x00
};

static const uint8_t PlayerBGUpperExtent__data[] = {
    0x20, 0x10
};

static const uint8_t AreaChangeTimerData__data[] = {
    0xa0, 0x34
};

static const uint8_t ClimbXPosAdder__data[] = {
    0xf9, 0x07
};

static const uint8_t ClimbPLocAdder__data[] = {
    0xff, 0x00
};

static const uint8_t FlagpoleYPosData__data[] = {
    0x18, 0x22, 0x50, 0x68, 0x90
};

static const uint8_t SolidMTileUpperExt__data[] = {
    0x10, 0x61, 0x88, 0xc4
};

static const uint8_t ClimbMTileUpperExt__data[] = {
    0x24, 0x6d, 0x8a, 0xc6
};

static const uint8_t EnemyBGCStateData__data[] = {
    0x01, 0x01, 0x02, 0x02, 0x02, 0x05
};

static const uint8_t EnemyBGCXSpdData__data[] = {
    0x10, 0xf0
};

static const uint8_t BoundBoxCtrlData__data[] = {
    0x02, 0x08, 0x0e, 0x20,
    0x03, 0x14, 0x0d, 0x20,
    0x02, 0x14, 0x0e, 0x20,
    0x02, 0x09, 0x0e, 0x15,
    0x00, 0x00, 0x18, 0x06,
    0x00, 0x00, 0x20, 0x0d,
    0x00, 0x00, 0x30, 0x0d,
    0x00, 0x00, 0x08, 0x08,
    0x06, 0x04, 0x0a, 0x08,
    0x03, 0x0e, 0x0d, 0x14,
    0x00, 0x02, 0x10, 0x15,
    0x04, 0x04, 0x0c, 0x1c
};

static const uint8_t BlockBufferAdderData__data[] = {
    0x00, 0x07, 0x0e
};

static const uint8_t BlockBuffer_X_Adder__data[] = {
    0x08, 0x03, 0x0c, 0x02, 0x02, 0x0d, 0x0d, 0x08,
    0x03, 0x0c, 0x02, 0x02, 0x0d, 0x0d, 0x08, 0x03,
    0x0c, 0x02, 0x02, 0x0d, 0x0d, 0x08, 0x00, 0x10,
    0x04, 0x14, 0x04, 0x04
};

static const uint8_t BlockBuffer_Y_Adder__data[] = {
    0x04, 0x20, 0x20, 0x08, 0x18, 0x08, 0x18, 0x02,
    0x20, 0x20, 0x08, 0x18, 0x08, 0x18, 0x12, 0x20,
    0x20, 0x18, 0x18, 0x18, 0x18, 0x18, 0x14, 0x14,
    0x06, 0x06, 0x08, 0x10
};

static const uint8_t VineYPosAdder__data[] = {
    0x00, 0x30
};

static const uint8_t FirstSprXPos__data[] = {
    0x04, 0x00, 0x04, 0x00
};

static const uint8_t FirstSprYPos__data[] = {
    0x00, 0x04, 0x00, 0x04
};

static const uint8_t SecondSprXPos__data[] = {
    0x00, 0x08, 0x00, 0x08
};

static const uint8_t SecondSprYPos__data[] = {
    0x08, 0x00, 0x08, 0x00
};

static const uint8_t FirstSprTilenum__data[] = {
    0x80, 0x82, 0x81, 0x83
};

static const uint8_t SecondSprTilenum__data[] = {
    0x81, 0x83, 0x80, 0x82
};

static const uint8_t HammerSprAttrib__data[] = {
    0x03, 0x03, 0xc3, 0xc3
};

static const uint8_t FlagpoleScoreNumTiles__data[] = {
    0xf9, 0x50,
    0xf7, 0x50,
    0xfa, 0xfb,
    0xf8, 0xfb,
    0xf6, 0xfb
};

static const uint8_t JumpingCoinTiles__data[] = {
    0x60, 0x61, 0x62, 0x63
};

static const uint8_t PowerUpGfxTable__data[] = {
    0x76, 0x77, 0x78, 0x79,
    0xd6, 0xd6, 0xd9, 0xd9,
    0x8d, 0x8d, 0xe4, 0xe4,
    0x76, 0x77, 0x78, 0x79
};

static const uint8_t PowerUpAttributes__data[] = {
    0x02, 0x01, 0x02, 0x01
};

static const uint8_t EnemyGraphicsTable__data[] = {
    0xfc, 0xfc, 0xaa, 0xab, 0xac, 0xad,
    0xfc, 0xfc, 0xae, 0xaf, 0xb0, 0xb1,
    0xfc, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9,
    0xfc, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
    0x69, 0xa5, 0x6a, 0xa7, 0xa8, 0xa9,
    0x6b, 0xa0, 0x6c, 0xa2, 0xa3, 0xa4,
    0xfc, 0xfc, 0x96, 0x97, 0x98, 0x99,
    0xfc, 0xfc, 0x9a, 0x9b, 0x9c, 0x9d,
    0xfc, 0xfc, 0x8f, 0x8e, 0x8e, 0x8f,
    0xfc, 0xfc, 0x95, 0x94, 0x94, 0x95,
    0xfc, 0xfc, 0xdc, 0xdc, 0xdf, 0xdf,
    0xdc, 0xdc, 0xdd, 0xdd, 0xde, 0xde,
    0xfc, 0xfc, 0xb2, 0xb3, 0xb4, 0xb5,
    0xfc, 0xfc, 0xb6, 0xb3, 0xb7, 0xb5,
    0xfc, 0xfc, 0x70, 0x71, 0x72, 0x73,
    0xfc, 0xfc, 0x6e, 0x6e, 0x6f, 0x6f,
    0xfc, 0xfc, 0x6d, 0x6d, 0x6f, 0x6f,
    0xfc, 0xfc, 0x6f, 0x6f, 0x6e, 0x6e,
    0xfc, 0xfc, 0x6f, 0x6f, 0x6d, 0x6d,
    0xfc, 0xfc, 0xf4, 0xf4, 0xf5, 0xf5,
    0xfc, 0xfc, 0xf4, 0xf4, 0xf5, 0xf5,
    0xfc, 0xfc, 0xf5, 0xf5, 0xf4, 0xf4,
    0xfc, 0xfc, 0xf5, 0xf5, 0xf4, 0xf4,
    0xfc, 0xfc, 0xfc, 0xfc, 0xef, 0xef,
    0xb9, 0xb8, 0xbb, 0xba, 0xbc, 0xbc,
    0xfc, 0xfc, 0xbd, 0xbd, 0xbc, 0xbc,
    0x7a, 0x7b, 0xda, 0xdb, 0xd8, 0xd8,
    0xcd, 0xcd, 0xce, 0xce, 0xcf, 0xcf,
    0x7d, 0x7c, 0xd1, 0x8c, 0xd3, 0xd2,
    0x7d, 0x7c, 0x89, 0x88, 0x8b, 0x8a,
    0xd5, 0xd4, 0xe3, 0xe2, 0xd3, 0xd2,
    0xd5, 0xd4, 0xe3, 0xe2, 0x8b, 0x8a,
    0xe5, 0xe5, 0xe6, 0xe6, 0xeb, 0xeb,
    0xec, 0xec, 0xed, 0xed, 0xee, 0xee,
    0xfc, 0xfc, 0xd0, 0xd0, 0xd7, 0xd7,
    0xbf, 0xbe, 0xc1, 0xc0, 0xc2, 0xfc,
    0xc4, 0xc3, 0xc6, 0xc5, 0xc8, 0xc7,
    0xbf, 0xbe, 0xca, 0xc9, 0xc2, 0xfc,
    0xc4, 0xc3, 0xc6, 0xc5, 0xcc, 0xcb,
    0xfc, 0xfc, 0xe8, 0xe7, 0xea, 0xe9,
    0xf2, 0xf2, 0xf3, 0xf3, 0xf2, 0xf2,
    0xf1, 0xf1, 0xf1, 0xf1, 0xfc, 0xfc,
    0xf0, 0xf0, 0xfc, 0xfc, 0xfc, 0xfc
};

static const uint8_t EnemyGfxTableOffsets__data[] = {
    0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0xa8, 0x54, 0x3c,
    0xea, 0x18, 0x48, 0x48, 0xcc, 0xc0, 0x18, 0x18,
    0x18, 0x90, 0x24, 0xff, 0x48, 0x9c, 0xd2, 0xd8,
    0xf0, 0xf6, 0xfc
};

static const uint8_t EnemyAttributeData__data[] = {
    0x01, 0x02, 0x03, 0x02, 0x01, 0x01, 0x03, 0x03,
    0x03, 0x01, 0x01, 0x02, 0x02, 0x21, 0x01, 0x02,
    0x01, 0x01, 0x02, 0xff, 0x02, 0x02, 0x01, 0x01,
    0x02, 0x02, 0x02
};

static const uint8_t EnemyAnimTimingBMask__data[] = {
    0x08, 0x18
};

static const uint8_t JumpspringFrameOffsets__data[] = {
    0x18, 0x19, 0x1a, 0x19, 0x18
};

static const uint8_t DefaultBlockObjTiles__data[] = {
    0x85, 0x85, 0x86, 0x86
};

static const uint8_t ExplosionTiles__data[] = {
    0x68, 0x67, 0x66
};

static const uint8_t PlayerGfxTblOffsets__data[] = {
    0x20, 0x28, 0xc8, 0x18, 0x00, 0x40, 0x50, 0x58,
    0x80, 0x88, 0xb8, 0x78, 0x60, 0xa0, 0xb0, 0xb8
};

static const uint8_t PlayerGraphicsTable__data[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x08, 0x09, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x30, 0x2c, 0x2d,
    0x08, 0x09, 0x0a, 0x0b, 0x2e, 0x2f, 0x2c, 0x2d,
    0x08, 0x09, 0x28, 0x29, 0x2a, 0x2b, 0x5c, 0x5d,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x5e, 0x5f,
    0xfc, 0xfc, 0x08, 0x09, 0x58, 0x59, 0x5a, 0x5a,
    0x08, 0x09, 0x28, 0x29, 0x2a, 0x2b, 0x0e, 0x0f,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x33, 0x34, 0x35,
    0xfc, 0xfc, 0xfc, 0xfc, 0x36, 0x37, 0x38, 0x39,
    0xfc, 0xfc, 0xfc, 0xfc, 0x3a, 0x37, 0x3b, 0x3c,
    0xfc, 0xfc, 0xfc, 0xfc, 0x3d, 0x3e, 0x3f, 0x40,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x41, 0x42, 0x43,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x33, 0x44, 0x45,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x33, 0x44, 0x47,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x33, 0x48, 0x49,
    0xfc, 0xfc, 0xfc, 0xfc, 0x32, 0x33, 0x90, 0x91,
    0xfc, 0xfc, 0xfc, 0xfc, 0x3a, 0x37, 0x92, 0x93,
    0xfc, 0xfc, 0xfc, 0xfc, 0x9e, 0x9e, 0x9f, 0x9f,
    0xfc, 0xfc, 0xfc, 0xfc, 0x3a, 0x37, 0x4f, 0x4f,
    0xfc, 0xfc, 0x00, 0x01, 0x4c, 0x4d, 0x4e, 0x4e,
    0x00, 0x01, 0x4c, 0x4d, 0x4a, 0x4a, 0x4b, 0x4b
};

static const uint8_t SwimKickTileNum__data[] = {
    0x31, 0x46
};

static const uint8_t IntermediatePlayerData__data[] = {
    0x58, 0x01, 0x00, 0x60, 0xff, 0x04
};

static const uint8_t ChangeSizeOffsetAdder__data[] = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02,
    0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00
};

static const uint8_t ObjOffsetData__data[] = {
    0x07, 0x16, 0x0d
};

static const uint8_t XOffscreenBitsData__data[] = {
    0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
    0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff
};

static const uint8_t DefaultXOnscreenOfs__data[] = {
    0x07, 0x0f, 0x07
};

static const uint8_t YOffscreenBitsData__data[] = {
    0x00, 0x08, 0x0c, 0x0e,
    0x0f, 0x07, 0x03, 0x01,
    0x00
};

static const uint8_t DefaultYOnscreenOfs__data[] = {
    0x04, 0x00, 0x04
};

static const uint8_t HighPosUnitData__data[] = {
    0xff, 0x00
};

static const uint8_t SwimStompEnvelopeData__data[] = {
    0x9f, 0x9b, 0x98, 0x96, 0x95, 0x94, 0x92, 0x90,
    0x90, 0x9a, 0x97, 0x95, 0x93, 0x92
};

static const uint8_t ExtraLifeFreqData__data[] = {
    0x58, 0x02, 0x54, 0x56, 0x4e, 0x44
};

static const uint8_t PowerUpGrabFreqData__data[] = {
    0x4c, 0x52, 0x4c, 0x48, 0x3e, 0x36, 0x3e, 0x36, 0x30,
    0x28, 0x4a, 0x50, 0x4a, 0x64, 0x3c, 0x32, 0x3c, 0x32,
    0x2c, 0x24, 0x3a, 0x64, 0x3a, 0x34, 0x2c, 0x22, 0x2c,
    0x22, 0x1c, 0x14
};

static const uint8_t PUp_VGrow_FreqData__data[] = {
    0x14, 0x04, 0x22, 0x24, 0x16, 0x04, 0x24, 0x26,
    0x18, 0x04, 0x26, 0x28, 0x1a, 0x04, 0x28, 0x2a,
    0x1c, 0x04, 0x2a, 0x2c, 0x1e, 0x04, 0x2c, 0x2e,
    0x20, 0x04, 0x2e, 0x30, 0x22, 0x04, 0x30, 0x32
};

static const uint8_t BrickShatterFreqData__data[] = {
    0x01, 0x0e, 0x0e, 0x0d, 0x0b, 0x06, 0x0c, 0x0f,
    0x0a, 0x09, 0x03, 0x0d, 0x08, 0x0d, 0x06, 0x0c
};

static const uint8_t MusicHeaderData__data[] = {
    DeathMusHdr - MHD,
    GameOverMusHdr - MHD,
    VictoryMusHdr - MHD,
    WinCastleMusHdr - MHD,
    GameOverMusHdr - MHD,
    EndOfLevelMusHdr - MHD,
    TimeRunningOutHdr - MHD,
    SilenceHdr - MHD,
    GroundLevelPart1Hdr - MHD,
    WaterMusHdr - MHD,
    UndergroundMusHdr - MHD,
    CastleMusHdr - MHD,
    Star_CloudHdr - MHD,
    GroundLevelLeadInHdr - MHD,
    Star_CloudHdr - MHD,
    SilenceHdr - MHD,
    GroundLevelLeadInHdr - MHD,
    GroundLevelPart1Hdr - MHD, GroundLevelPart1Hdr - MHD,
    GroundLevelPart2AHdr - MHD, GroundLevelPart2BHdr - MHD, GroundLevelPart2AHdr - MHD, GroundLevelPart2CHdr - MHD,
    GroundLevelPart2AHdr - MHD, GroundLevelPart2BHdr - MHD, GroundLevelPart2AHdr - MHD, GroundLevelPart2CHdr - MHD,
    GroundLevelPart3AHdr - MHD, GroundLevelPart3BHdr - MHD, GroundLevelPart3AHdr - MHD, GroundLevelLeadInHdr - MHD,
    GroundLevelPart1Hdr - MHD, GroundLevelPart1Hdr - MHD,
    GroundLevelPart4AHdr - MHD, GroundLevelPart4BHdr - MHD, GroundLevelPart4AHdr - MHD, GroundLevelPart4CHdr - MHD,
    GroundLevelPart4AHdr - MHD, GroundLevelPart4BHdr - MHD, GroundLevelPart4AHdr - MHD, GroundLevelPart4CHdr - MHD,
    GroundLevelPart3AHdr - MHD, GroundLevelPart3BHdr - MHD, GroundLevelPart3AHdr - MHD, GroundLevelLeadInHdr - MHD,
    GroundLevelPart4AHdr - MHD, GroundLevelPart4BHdr - MHD, GroundLevelPart4AHdr - MHD, GroundLevelPart4CHdr - MHD
};

static const uint8_t TimeRunningOutHdr__data[] = {
    0x08, LOBYTE(TimeRunOutMusData), HIBYTE(TimeRunOutMusData), 0x27, 0x18
};

static const uint8_t Star_CloudHdr__data[] = {
    0x20, LOBYTE(Star_CloudMData), HIBYTE(Star_CloudMData), 0x2e, 0x1a, 0x40
};

static const uint8_t EndOfLevelMusHdr__data[] = {
    0x20, LOBYTE(WinLevelMusData), HIBYTE(WinLevelMusData), 0x3d, 0x21
};

static const uint8_t ResidualHeaderData__data[] = {
    0x20, 0xc4, 0xfc, 0x3f, 0x1d
};

static const uint8_t UndergroundMusHdr__data[] = {
    0x18, LOBYTE(UndergroundMusData), HIBYTE(UndergroundMusData), 0x00, 0x00
};

static const uint8_t SilenceHdr__data[] = {
    0x08, LOBYTE(SilenceData), HIBYTE(SilenceData), 0x00
};

static const uint8_t CastleMusHdr__data[] = {
    0x00, LOBYTE(CastleMusData), HIBYTE(CastleMusData), 0x93, 0x62
};

static const uint8_t VictoryMusHdr__data[] = {
    0x10, LOBYTE(VictoryMusData), HIBYTE(VictoryMusData), 0x24, 0x14
};

static const uint8_t GameOverMusHdr__data[] = {
    0x18, LOBYTE(GameOverMusData), HIBYTE(GameOverMusData), 0x1e, 0x14
};

static const uint8_t WaterMusHdr__data[] = {
    0x08, LOBYTE(WaterMusData), HIBYTE(WaterMusData), 0xa0, 0x70, 0x68
};

static const uint8_t WinCastleMusHdr__data[] = {
    0x08, LOBYTE(EndOfCastleMusData), HIBYTE(EndOfCastleMusData), 0x4c, 0x24
};

static const uint8_t GroundLevelPart1Hdr__data[] = {
    0x18, LOBYTE(GroundM_P1Data), HIBYTE(GroundM_P1Data), 0x2d, 0x1c, 0xb8
};

static const uint8_t GroundLevelPart2AHdr__data[] = {
    0x18, LOBYTE(GroundM_P2AData), HIBYTE(GroundM_P2AData), 0x20, 0x12, 0x70
};

static const uint8_t GroundLevelPart2BHdr__data[] = {
    0x18, LOBYTE(GroundM_P2BData), HIBYTE(GroundM_P2BData), 0x1b, 0x10, 0x44
};

static const uint8_t GroundLevelPart2CHdr__data[] = {
    0x18, LOBYTE(GroundM_P2CData), HIBYTE(GroundM_P2CData), 0x11, 0x0a, 0x1c
};

static const uint8_t GroundLevelPart3AHdr__data[] = {
    0x18, LOBYTE(GroundM_P3AData), HIBYTE(GroundM_P3AData), 0x2d, 0x10, 0x58
};

static const uint8_t GroundLevelPart3BHdr__data[] = {
    0x18, LOBYTE(GroundM_P3BData), HIBYTE(GroundM_P3BData), 0x14, 0x0d, 0x3f
};

static const uint8_t GroundLevelLeadInHdr__data[] = {
    0x18, LOBYTE(GroundMLdInData), HIBYTE(GroundMLdInData), 0x15, 0x0d, 0x21
};

static const uint8_t GroundLevelPart4AHdr__data[] = {
    0x18, LOBYTE(GroundM_P4AData), HIBYTE(GroundM_P4AData), 0x18, 0x10, 0x7a
};

static const uint8_t GroundLevelPart4BHdr__data[] = {
    0x18, LOBYTE(GroundM_P4BData), HIBYTE(GroundM_P4BData), 0x19, 0x0f, 0x54
};

static const uint8_t GroundLevelPart4CHdr__data[] = {
    0x18, LOBYTE(GroundM_P4CData), HIBYTE(GroundM_P4CData), 0x1e, 0x12, 0x2b
};

static const uint8_t DeathMusHdr__data[] = {
    0x18, LOBYTE(DeathMusData), HIBYTE(DeathMusData), 0x1e, 0x0f, 0x2d
};

static const uint8_t Star_CloudMData__data[] = {
    0x84, 0x2c, 0x2c, 0x2c, 0x82, 0x04, 0x2c, 0x04, 0x85, 0x2c, 0x84, 0x2c, 0x2c,
    0x2a, 0x2a, 0x2a, 0x82, 0x04, 0x2a, 0x04, 0x85, 0x2a, 0x84, 0x2a, 0x2a, 0x00,
    0x1f, 0x1f, 0x1f, 0x98, 0x1f, 0x1f, 0x98, 0x9e, 0x98, 0x1f,
    0x1d, 0x1d, 0x1d, 0x94, 0x1d, 0x1d, 0x94, 0x9c, 0x94, 0x1d,
    0x86, 0x18, 0x85, 0x26, 0x30, 0x84, 0x04, 0x26, 0x30,
    0x86, 0x14, 0x85, 0x22, 0x2c, 0x84, 0x04, 0x22, 0x2c,
    0x21, 0xd0, 0xc4, 0xd0, 0x31, 0xd0, 0xc4, 0xd0, 0x00
};

static const uint8_t GroundM_P1Data__data[] = {
    0x85, 0x2c, 0x22, 0x1c, 0x84, 0x26, 0x2a, 0x82, 0x28, 0x26, 0x04,
    0x87, 0x22, 0x34, 0x3a, 0x82, 0x40, 0x04, 0x36, 0x84, 0x3a, 0x34,
    0x82, 0x2c, 0x30, 0x85, 0x2a
};

static const uint8_t SilenceData__data[] = {
    0x00,
    0x5d, 0x55, 0x4d, 0x15, 0x19, 0x96, 0x15, 0xd5, 0xe3, 0xeb,
    0x2d, 0xa6, 0x2b, 0x27, 0x9c, 0x9e, 0x59,
    0x85, 0x22, 0x1c, 0x14, 0x84, 0x1e, 0x22, 0x82, 0x20, 0x1e, 0x04, 0x87,
    0x1c, 0x2c, 0x34, 0x82, 0x36, 0x04, 0x30, 0x34, 0x04, 0x2c, 0x04, 0x26,
    0x2a, 0x85, 0x22
};

static const uint8_t GroundM_P2AData__data[] = {
    0x84, 0x04, 0x82, 0x3a, 0x38, 0x36, 0x32, 0x04, 0x34,
    0x04, 0x24, 0x26, 0x2c, 0x04, 0x26, 0x2c, 0x30, 0x00,
    0x05, 0xb4, 0xb2, 0xb0, 0x2b, 0xac, 0x84,
    0x9c, 0x9e, 0xa2, 0x84, 0x94, 0x9c, 0x9e,
    0x85, 0x14, 0x22, 0x84, 0x2c, 0x85, 0x1e,
    0x82, 0x2c, 0x84, 0x2c, 0x1e
};

static const uint8_t GroundM_P2BData__data[] = {
    0x84, 0x04, 0x82, 0x3a, 0x38, 0x36, 0x32, 0x04, 0x34,
    0x04, 0x64, 0x04, 0x64, 0x86, 0x64, 0x00,
    0x05, 0xb4, 0xb2, 0xb0, 0x2b, 0xac, 0x84,
    0x37, 0xb6, 0xb6, 0x45,
    0x85, 0x14, 0x1c, 0x82, 0x22, 0x84, 0x2c,
    0x4e, 0x82, 0x4e, 0x84, 0x4e, 0x22
};

static const uint8_t GroundM_P2CData__data[] = {
    0x84, 0x04, 0x85, 0x32, 0x85, 0x30, 0x86, 0x2c, 0x04, 0x00,
    0x05, 0xa4, 0x05, 0x9e, 0x05, 0x9d, 0x85,
    0x84, 0x14, 0x85, 0x24, 0x28, 0x2c, 0x82,
    0x22, 0x84, 0x22, 0x14,
    0x21, 0xd0, 0xc4, 0xd0, 0x31, 0xd0, 0xc4, 0xd0, 0x00
};

static const uint8_t GroundM_P3AData__data[] = {
    0x82, 0x2c, 0x84, 0x2c, 0x2c, 0x82, 0x2c, 0x30,
    0x04, 0x34, 0x2c, 0x04, 0x26, 0x86, 0x22, 0x00,
    0xa4, 0x25, 0x25, 0xa4, 0x29, 0xa2, 0x1d, 0x9c, 0x95
};

static const uint8_t GroundM_P3BData__data[] = {
    0x82, 0x2c, 0x2c, 0x04, 0x2c, 0x04, 0x2c, 0x30, 0x85, 0x34, 0x04, 0x04, 0x00,
    0xa4, 0x25, 0x25, 0xa4, 0xa8, 0x63, 0x04,
    0x85, 0x0e, 0x1a, 0x84, 0x24, 0x85, 0x22, 0x14, 0x84, 0x0c
};

static const uint8_t GroundMLdInData__data[] = {
    0x82, 0x34, 0x84, 0x34, 0x34, 0x82, 0x2c, 0x84, 0x34, 0x86, 0x3a, 0x04, 0x00,
    0xa0, 0x21, 0x21, 0xa0, 0x21, 0x2b, 0x05, 0xa3,
    0x82, 0x18, 0x84, 0x18, 0x18, 0x82, 0x18, 0x18, 0x04, 0x86, 0x3a, 0x22,
    0x31, 0x90, 0x31, 0x90, 0x31, 0x71, 0x31, 0x90, 0x90, 0x90, 0x00
};

static const uint8_t GroundM_P4AData__data[] = {
    0x82, 0x34, 0x84, 0x2c, 0x85, 0x22, 0x84, 0x24,
    0x82, 0x26, 0x36, 0x04, 0x36, 0x86, 0x26, 0x00,
    0xac, 0x27, 0x5d, 0x1d, 0x9e, 0x2d, 0xac, 0x9f,
    0x85, 0x14, 0x82, 0x20, 0x84, 0x22, 0x2c,
    0x1e, 0x1e, 0x82, 0x2c, 0x2c, 0x1e, 0x04
};

static const uint8_t GroundM_P4BData__data[] = {
    0x87, 0x2a, 0x40, 0x40, 0x40, 0x3a, 0x36,
    0x82, 0x34, 0x2c, 0x04, 0x26, 0x86, 0x22, 0x00,
    0xe3, 0xf7, 0xf7, 0xf7, 0xf5, 0xf1, 0xac, 0x27, 0x9e, 0x9d,
    0x85, 0x18, 0x82, 0x1e, 0x84, 0x22, 0x2a,
    0x22, 0x22, 0x82, 0x2c, 0x2c, 0x22, 0x04
};

static const uint8_t DeathMusData__data[] = {
    0x86, 0x04
};

static const uint8_t GroundM_P4CData__data[] = {
    0x82, 0x2a, 0x36, 0x04, 0x36, 0x87, 0x36, 0x34, 0x30, 0x86, 0x2c, 0x04, 0x00,
    0x00, 0x68, 0x6a, 0x6c, 0x45,
    0xa2, 0x31, 0xb0, 0xf1, 0xed, 0xeb, 0xa2, 0x1d, 0x9c, 0x95,
    0x86, 0x04,
    0x85, 0x22, 0x82, 0x22, 0x87, 0x22, 0x26, 0x2a, 0x84, 0x2c, 0x22, 0x86, 0x14,
    0x51, 0x90, 0x31, 0x11, 0x00
};

static const uint8_t CastleMusData__data[] = {
    0x80, 0x22, 0x28, 0x22, 0x26, 0x22, 0x24, 0x22, 0x26,
    0x22, 0x28, 0x22, 0x2a, 0x22, 0x28, 0x22, 0x26,
    0x22, 0x28, 0x22, 0x26, 0x22, 0x24, 0x22, 0x26,
    0x22, 0x28, 0x22, 0x2a, 0x22, 0x28, 0x22, 0x26,
    0x20, 0x26, 0x20, 0x24, 0x20, 0x26, 0x20, 0x28,
    0x20, 0x26, 0x20, 0x28, 0x20, 0x26, 0x20, 0x24,
    0x20, 0x26, 0x20, 0x24, 0x20, 0x26, 0x20, 0x28,
    0x20, 0x26, 0x20, 0x28, 0x20, 0x26, 0x20, 0x24,
    0x28, 0x30, 0x28, 0x32, 0x28, 0x30, 0x28, 0x2e,
    0x28, 0x30, 0x28, 0x2e, 0x28, 0x2c, 0x28, 0x2e,
    0x28, 0x30, 0x28, 0x32, 0x28, 0x30, 0x28, 0x2e,
    0x28, 0x30, 0x28, 0x2e, 0x28, 0x2c, 0x28, 0x2e, 0x00,
    0x04, 0x70, 0x6e, 0x6c, 0x6e, 0x70, 0x72, 0x70, 0x6e,
    0x70, 0x6e, 0x6c, 0x6e, 0x70, 0x72, 0x70, 0x6e,
    0x6e, 0x6c, 0x6e, 0x70, 0x6e, 0x70, 0x6e, 0x6c,
    0x6e, 0x6c, 0x6e, 0x70, 0x6e, 0x70, 0x6e, 0x6c,
    0x76, 0x78, 0x76, 0x74, 0x76, 0x74, 0x72, 0x74,
    0x76, 0x78, 0x76, 0x74, 0x76, 0x74, 0x72, 0x74,
    0x84, 0x1a, 0x83, 0x18, 0x20, 0x84, 0x1e, 0x83, 0x1c, 0x28,
    0x26, 0x1c, 0x1a, 0x1c
};

static const uint8_t GameOverMusData__data[] = {
    0x82, 0x2c, 0x04, 0x04, 0x22, 0x04, 0x04, 0x84, 0x1c, 0x87,
    0x26, 0x2a, 0x26, 0x84, 0x24, 0x28, 0x24, 0x80, 0x22, 0x00,
    0x9c, 0x05, 0x94, 0x05, 0x0d, 0x9f, 0x1e, 0x9c, 0x98, 0x9d,
    0x82, 0x22, 0x04, 0x04, 0x1c, 0x04, 0x04, 0x84, 0x14,
    0x86, 0x1e, 0x80, 0x16, 0x80, 0x14
};

static const uint8_t TimeRunOutMusData__data[] = {
    0x81, 0x1c, 0x30, 0x04, 0x30, 0x30, 0x04, 0x1e, 0x32, 0x04, 0x32, 0x32,
    0x04, 0x20, 0x34, 0x04, 0x34, 0x34, 0x04, 0x36, 0x04, 0x84, 0x36, 0x00,
    0x46, 0xa4, 0x64, 0xa4, 0x48, 0xa6, 0x66, 0xa6, 0x4a, 0xa8, 0x68, 0xa8,
    0x6a, 0x44, 0x2b,
    0x81, 0x2a, 0x42, 0x04, 0x42, 0x42, 0x04, 0x2c, 0x64, 0x04, 0x64, 0x64,
    0x04, 0x2e, 0x46, 0x04, 0x46, 0x46, 0x04, 0x22, 0x04, 0x84, 0x22
};

static const uint8_t WinLevelMusData__data[] = {
    0x87, 0x04, 0x06, 0x0c, 0x14, 0x1c, 0x22, 0x86, 0x2c, 0x22,
    0x87, 0x04, 0x60, 0x0e, 0x14, 0x1a, 0x24, 0x86, 0x2c, 0x24,
    0x87, 0x04, 0x08, 0x10, 0x18, 0x1e, 0x28, 0x86, 0x30, 0x30,
    0x80, 0x64, 0x00,
    0xcd, 0xd5, 0xdd, 0xe3, 0xed, 0xf5, 0xbb, 0xb5, 0xcf, 0xd5,
    0xdb, 0xe5, 0xed, 0xf3, 0xbd, 0xb3, 0xd1, 0xd9, 0xdf, 0xe9,
    0xf1, 0xf7, 0xbf, 0xff, 0xff, 0xff, 0x34,
    0x00,
    0x86, 0x04, 0x87, 0x14, 0x1c, 0x22, 0x86, 0x34, 0x84, 0x2c,
    0x04, 0x04, 0x04, 0x87, 0x14, 0x1a, 0x24, 0x86, 0x32, 0x84,
    0x2c, 0x04, 0x86, 0x04, 0x87, 0x18, 0x1e, 0x28, 0x86, 0x36,
    0x87, 0x30, 0x30, 0x30, 0x80, 0x2c
};

static const uint8_t UndergroundMusData__data[] = {
    0x82, 0x14, 0x2c, 0x62, 0x26, 0x10, 0x28, 0x80, 0x04,
    0x82, 0x14, 0x2c, 0x62, 0x26, 0x10, 0x28, 0x80, 0x04,
    0x82, 0x08, 0x1e, 0x5e, 0x18, 0x60, 0x1a, 0x80, 0x04,
    0x82, 0x08, 0x1e, 0x5e, 0x18, 0x60, 0x1a, 0x86, 0x04,
    0x83, 0x1a, 0x18, 0x16, 0x84, 0x14, 0x1a, 0x18, 0x0e, 0x0c,
    0x16, 0x83, 0x14, 0x20, 0x1e, 0x1c, 0x28, 0x26, 0x87,
    0x24, 0x1a, 0x12, 0x10, 0x62, 0x0e, 0x80, 0x04, 0x04,
    0x00
};

static const uint8_t WaterMusData__data[] = {
    0x82, 0x18, 0x1c, 0x20, 0x22, 0x26, 0x28,
    0x81, 0x2a, 0x2a, 0x2a, 0x04, 0x2a, 0x04, 0x83, 0x2a, 0x82, 0x22,
    0x86, 0x34, 0x32, 0x34, 0x81, 0x04, 0x22, 0x26, 0x2a, 0x2c, 0x30,
    0x86, 0x34, 0x83, 0x32, 0x82, 0x36, 0x84, 0x34, 0x85, 0x04, 0x81, 0x22,
    0x86, 0x30, 0x2e, 0x30, 0x81, 0x04, 0x22, 0x26, 0x2a, 0x2c, 0x2e,
    0x86, 0x30, 0x83, 0x22, 0x82, 0x36, 0x84, 0x34, 0x85, 0x04, 0x81, 0x22,
    0x86, 0x3a, 0x3a, 0x3a, 0x82, 0x3a, 0x81, 0x40, 0x82, 0x04, 0x81, 0x3a,
    0x86, 0x36, 0x36, 0x36, 0x82, 0x36, 0x81, 0x3a, 0x82, 0x04, 0x81, 0x36,
    0x86, 0x34, 0x82, 0x26, 0x2a, 0x36,
    0x81, 0x34, 0x34, 0x85, 0x34, 0x81, 0x2a, 0x86, 0x2c, 0x00,
    0x84, 0x90, 0xb0, 0x84, 0x50, 0x50, 0xb0, 0x00,
    0x98, 0x96, 0x94, 0x92, 0x94, 0x96, 0x58, 0x58, 0x58, 0x44,
    0x5c, 0x44, 0x9f, 0xa3, 0xa1, 0xa3, 0x85, 0xa3, 0xe0, 0xa6,
    0x23, 0xc4, 0x9f, 0x9d, 0x9f, 0x85, 0x9f, 0xd2, 0xa6, 0x23,
    0xc4, 0xb5, 0xb1, 0xaf, 0x85, 0xb1, 0xaf, 0xad, 0x85, 0x95,
    0x9e, 0xa2, 0xaa, 0x6a, 0x6a, 0x6b, 0x5e, 0x9d,
    0x84, 0x04, 0x04, 0x82, 0x22, 0x86, 0x22,
    0x82, 0x14, 0x22, 0x2c, 0x12, 0x22, 0x2a, 0x14, 0x22, 0x2c,
    0x1c, 0x22, 0x2c, 0x14, 0x22, 0x2c, 0x12, 0x22, 0x2a, 0x14,
    0x22, 0x2c, 0x1c, 0x22, 0x2c, 0x18, 0x22, 0x2a, 0x16, 0x20,
    0x28, 0x18, 0x22, 0x2a, 0x12, 0x22, 0x2a, 0x18, 0x22, 0x2a,
    0x12, 0x22, 0x2a, 0x14, 0x22, 0x2c, 0x0c, 0x22, 0x2c, 0x14, 0x22, 0x34, 0x12,
    0x22, 0x30, 0x10, 0x22, 0x2e, 0x16, 0x22, 0x34, 0x18, 0x26,
    0x36, 0x16, 0x26, 0x36, 0x14, 0x26, 0x36, 0x12, 0x22, 0x36,
    0x5c, 0x22, 0x34, 0x0c, 0x22, 0x22, 0x81, 0x1e, 0x1e, 0x85, 0x1e,
    0x81, 0x12, 0x86, 0x14
};

static const uint8_t EndOfCastleMusData__data[] = {
    0x81, 0x2c, 0x22, 0x1c, 0x2c, 0x22, 0x1c, 0x85, 0x2c, 0x04,
    0x81, 0x2e, 0x24, 0x1e, 0x2e, 0x24, 0x1e, 0x85, 0x2e, 0x04,
    0x81, 0x32, 0x28, 0x22, 0x32, 0x28, 0x22, 0x85, 0x32,
    0x87, 0x36, 0x36, 0x36, 0x84, 0x3a, 0x00,
    0x5c, 0x54, 0x4c, 0x5c, 0x54, 0x4c,
    0x5c, 0x1c, 0x1c, 0x5c, 0x5c, 0x5c, 0x5c,
    0x5e, 0x56, 0x4e, 0x5e, 0x56, 0x4e,
    0x5e, 0x1e, 0x1e, 0x5e, 0x5e, 0x5e, 0x5e,
    0x62, 0x5a, 0x50, 0x62, 0x5a, 0x50,
    0x62, 0x22, 0x22, 0x62, 0xe7, 0xe7, 0xe7, 0x2b,
    0x86, 0x14, 0x81, 0x14, 0x80, 0x14, 0x14, 0x81, 0x14, 0x14, 0x14, 0x14,
    0x86, 0x16, 0x81, 0x16, 0x80, 0x16, 0x16, 0x81, 0x16, 0x16, 0x16, 0x16,
    0x81, 0x28, 0x22, 0x1a, 0x28, 0x22, 0x1a, 0x28, 0x80, 0x28, 0x28,
    0x81, 0x28, 0x87, 0x2c, 0x2c, 0x2c, 0x84, 0x30
};

static const uint8_t VictoryMusData__data[] = {
    0x83, 0x04, 0x84, 0x0c, 0x83, 0x62, 0x10, 0x84, 0x12,
    0x83, 0x1c, 0x22, 0x1e, 0x22, 0x26, 0x18, 0x1e, 0x04, 0x1c, 0x00,
    0xe3, 0xe1, 0xe3, 0x1d, 0xde, 0xe0, 0x23,
    0xec, 0x75, 0x74, 0xf0, 0xf4, 0xf6, 0xea, 0x31, 0x2d,
    0x83, 0x12, 0x14, 0x04, 0x18, 0x1a, 0x1c, 0x14,
    0x26, 0x22, 0x1e, 0x1c, 0x18, 0x1e, 0x22, 0x0c, 0x14,
    0xff, 0xff, 0xff
};

static const uint8_t FreqRegLookupTbl__data[] = {
    0x00, 0x88, 0x00, 0x2f, 0x00, 0x00,
    0x02, 0xa6, 0x02, 0x80, 0x02, 0x5c, 0x02, 0x3a,
    0x02, 0x1a, 0x01, 0xdf, 0x01, 0xc4, 0x01, 0xab,
    0x01, 0x93, 0x01, 0x7c, 0x01, 0x67, 0x01, 0x53,
    0x01, 0x40, 0x01, 0x2e, 0x01, 0x1d, 0x01, 0x0d,
    0x00, 0xfe, 0x00, 0xef, 0x00, 0xe2, 0x00, 0xd5,
    0x00, 0xc9, 0x00, 0xbe, 0x00, 0xb3, 0x00, 0xa9,
    0x00, 0xa0, 0x00, 0x97, 0x00, 0x8e, 0x00, 0x86,
    0x00, 0x77, 0x00, 0x7e, 0x00, 0x71, 0x00, 0x54,
    0x00, 0x64, 0x00, 0x5f, 0x00, 0x59, 0x00, 0x50,
    0x00, 0x47, 0x00, 0x43, 0x00, 0x3b, 0x00, 0x35,
    0x00, 0x2a, 0x00, 0x23, 0x04, 0x75, 0x03, 0x57,
    0x02, 0xf9, 0x02, 0xcf, 0x01, 0xfc, 0x00, 0x6a
};

static const uint8_t MusicLengthLookupTbl__data[] = {
    0x05, 0x0a, 0x14, 0x28, 0x50, 0x1e, 0x3c, 0x02,
    0x04, 0x08, 0x10, 0x20, 0x40, 0x18, 0x30, 0x0c,
    0x03, 0x06, 0x0c, 0x18, 0x30, 0x12, 0x24, 0x08,
    0x36, 0x03, 0x09, 0x06, 0x12, 0x1b, 0x24, 0x0c,
    0x24, 0x02, 0x06, 0x04, 0x0c, 0x12, 0x18, 0x08,
    0x12, 0x01, 0x03, 0x02, 0x06, 0x09, 0x0c, 0x04
};

static const uint8_t EndOfCastleMusicEnvData__data[] = {
    0x98, 0x99, 0x9a, 0x9b
};

static const uint8_t AreaMusicEnvData__data[] = {
    0x90, 0x94, 0x94, 0x95, 0x95, 0x96, 0x97, 0x98
};

static const uint8_t WaterEventMusEnvData__data[] = {
    0x90, 0x91, 0x92, 0x92, 0x93, 0x93, 0x93, 0x94,
    0x94, 0x94, 0x94, 0x94, 0x94, 0x95, 0x95, 0x95,
    0x95, 0x95, 0x95, 0x96, 0x96, 0x96, 0x96, 0x96,
    0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96, 0x96,
    0x96, 0x96, 0x96, 0x96, 0x95, 0x95, 0x94, 0x93
};

static const uint8_t BowserFlameEnvData__data[] = {
    0x15, 0x16, 0x16, 0x17, 0x17, 0x18, 0x19, 0x19,
    0x1a, 0x1a, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1e, 0x1d, 0x1c, 0x1e, 0x1f,
    0x1f, 0x1e, 0x1d, 0x1c, 0x1a, 0x18, 0x16, 0x14
};

static const uint8_t BrickShatterEnvData__data[] = {
    0x15, 0x16, 0x16, 0x17, 0x17, 0x18, 0x19, 0x19,
    0x1a, 0x1a, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e, 0x1f
};

static void loadConstantData()
{
    writeData(VRAM_AddrTable_Low, VRAM_AddrTable_Low__data, 19);
    writeData(VRAM_AddrTable_High, VRAM_AddrTable_High__data, 19);
    writeData(VRAM_Buffer_Offset, VRAM_Buffer_Offset__data, 2);
    writeData(WSelectBufferTemplate, WSelectBufferTemplate__data, 6);
    writeData(MushroomIconData, MushroomIconData__data, 8);
    writeData(DemoActionData, DemoActionData__data, 21);
    writeData(DemoTimingData, DemoTimingData__data, 22);
    writeData(FloateyNumTileData, FloateyNumTileData__data, 24);
    writeData(ScoreUpdateData, ScoreUpdateData__data, 12);
    writeData(AreaPalette, AreaPalette__data, 4);
    writeData(BGColorCtrl_Addr, BGColorCtrl_Addr__data, 4);
    writeData(BackgroundColors, BackgroundColors__data, 8);
    writeData(PlayerColors, PlayerColors__data, 12);
    writeData(GameText, GameText__data, 0);
    writeData(TopStatusBarLine, TopStatusBarLine__data, 39);
    writeData(WorldLivesDisplay, WorldLivesDisplay__data, 31);
    writeData(TwoPlayerTimeUp, TwoPlayerTimeUp__data, 8);
    writeData(OnePlayerTimeUp, OnePlayerTimeUp__data, 11);
    writeData(TwoPlayerGameOver, TwoPlayerGameOver__data, 8);
    writeData(OnePlayerGameOver, OnePlayerGameOver__data, 13);
    writeData(WarpZoneWelcome, WarpZoneWelcome__data, 45);
    writeData(LuigiName, LuigiName__data, 5);
    writeData(WarpZoneNumbers, WarpZoneNumbers__data, 12);
    writeData(GameTextOffsets, GameTextOffsets__data, 10);
    writeData(ColorRotatePalette, ColorRotatePalette__data, 6);
    writeData(BlankPalette, BlankPalette__data, 8);
    writeData(Palette3Data, Palette3Data__data, 16);
    writeData(BlockGfxData, BlockGfxData__data, 20);
    writeData(MetatileGraphics_Low, MetatileGraphics_Low__data, 4);
    writeData(MetatileGraphics_High, MetatileGraphics_High__data, 4);
    writeData(Palette0_MTiles, Palette0_MTiles__data, 156);
    writeData(Palette1_MTiles, Palette1_MTiles__data, 184);
    writeData(Palette2_MTiles, Palette2_MTiles__data, 40);
    writeData(Palette3_MTiles, Palette3_MTiles__data, 24);
    writeData(WaterPaletteData, WaterPaletteData__data, 36);
    writeData(GroundPaletteData, GroundPaletteData__data, 36);
    writeData(UndergroundPaletteData, UndergroundPaletteData__data, 36);
    writeData(CastlePaletteData, CastlePaletteData__data, 36);
    writeData(DaySnowPaletteData, DaySnowPaletteData__data, 8);
    writeData(NightSnowPaletteData, NightSnowPaletteData__data, 8);
    writeData(MushroomPaletteData, MushroomPaletteData__data, 8);
    writeData(BowserPaletteData, BowserPaletteData__data, 8);
    writeData(MarioThanksMessage, MarioThanksMessage__data, 20);
    writeData(LuigiThanksMessage, LuigiThanksMessage__data, 20);
    writeData(MushroomRetainerSaved, MushroomRetainerSaved__data, 44);
    writeData(PrincessSaved1, PrincessSaved1__data, 23);
    writeData(PrincessSaved2, PrincessSaved2__data, 31);
    writeData(WorldSelectMessage1, WorldSelectMessage1__data, 17);
    writeData(WorldSelectMessage2, WorldSelectMessage2__data, 21);
    writeData(StatusBarData, StatusBarData__data, 12);
    writeData(StatusBarOffset, StatusBarOffset__data, 6);
    writeData(DefaultSprOffsets, DefaultSprOffsets__data, 15);
    writeData(Sprite0Data, Sprite0Data__data, 4);
    writeData(MusicSelectData, MusicSelectData__data, 6);
    writeData(PlayerStarting_X_Pos, PlayerStarting_X_Pos__data, 4);
    writeData(AltYPosOffset, AltYPosOffset__data, 2);
    writeData(PlayerStarting_Y_Pos, PlayerStarting_Y_Pos__data, 9);
    writeData(PlayerBGPriorityData, PlayerBGPriorityData__data, 8);
    writeData(GameTimerData, GameTimerData__data, 4);
    writeData(HalfwayPageNybbles, HalfwayPageNybbles__data, 16);
    writeData(BSceneDataOffsets, BSceneDataOffsets__data, 3);
    writeData(BackSceneryData, BackSceneryData__data, 144);
    writeData(BackSceneryMetatiles, BackSceneryMetatiles__data, 36);
    writeData(FSceneDataOffsets, FSceneDataOffsets__data, 3);
    writeData(ForeSceneryData, ForeSceneryData__data, 39);
    writeData(TerrainMetatiles, TerrainMetatiles__data, 4);
    writeData(TerrainRenderBits, TerrainRenderBits__data, 32);
    writeData(BlockBuffLowBounds, BlockBuffLowBounds__data, 4);
    writeData(FrenzyIDData, FrenzyIDData__data, 3);
    writeData(PulleyRopeMetatiles, PulleyRopeMetatiles__data, 3);
    writeData(CastleMetatiles, CastleMetatiles__data, 55);
    writeData(SidePipeShaftData, SidePipeShaftData__data, 4);
    writeData(SidePipeTopPart, SidePipeTopPart__data, 4);
    writeData(SidePipeBottomPart, SidePipeBottomPart__data, 4);
    writeData(VerticalPipeData, VerticalPipeData__data, 8);
    writeData(CoinMetatileData, CoinMetatileData__data, 4);
    writeData(C_ObjectRow, C_ObjectRow__data, 3);
    writeData(C_ObjectMetatile, C_ObjectMetatile__data, 3);
    writeData(SolidBlockMetatiles, SolidBlockMetatiles__data, 4);
    writeData(BrickMetatiles, BrickMetatiles__data, 5);
    writeData(StaircaseHeightData, StaircaseHeightData__data, 9);
    writeData(StaircaseRowData, StaircaseRowData__data, 9);
    writeData(HoleMetatiles, HoleMetatiles__data, 4);
    writeData(BlockBufferAddr, BlockBufferAddr__data, 4);
    writeData(AreaDataOfsLoopback, AreaDataOfsLoopback__data, 11);
    writeData(WorldAddrOffsets, WorldAddrOffsets__data, 8);
    writeData(AreaAddrOffsets, AreaAddrOffsets__data, 0);
    writeData(World1Areas, World1Areas__data, 5);
    writeData(World2Areas, World2Areas__data, 5);
    writeData(World3Areas, World3Areas__data, 4);
    writeData(World4Areas, World4Areas__data, 5);
    writeData(World5Areas, World5Areas__data, 4);
    writeData(World6Areas, World6Areas__data, 4);
    writeData(World7Areas, World7Areas__data, 5);
    writeData(World8Areas, World8Areas__data, 4);
    writeData(EnemyAddrHOffsets, EnemyAddrHOffsets__data, 4);
    writeData(EnemyDataAddrLow, EnemyDataAddrLow__data, 34);
    writeData(EnemyDataAddrHigh, EnemyDataAddrHigh__data, 34);
    writeData(AreaDataHOffsets, AreaDataHOffsets__data, 4);
    writeData(AreaDataAddrLow, AreaDataAddrLow__data, 34);
    writeData(AreaDataAddrHigh, AreaDataAddrHigh__data, 34);
    writeData(E_CastleArea1, E_CastleArea1__data, 39);
    writeData(E_CastleArea2, E_CastleArea2__data, 25);
    writeData(E_CastleArea3, E_CastleArea3__data, 47);
    writeData(E_CastleArea4, E_CastleArea4__data, 43);
    writeData(E_CastleArea5, E_CastleArea5__data, 21);
    writeData(E_CastleArea6, E_CastleArea6__data, 58);
    writeData(E_GroundArea1, E_GroundArea1__data, 37);
    writeData(E_GroundArea2, E_GroundArea2__data, 29);
    writeData(E_GroundArea3, E_GroundArea3__data, 14);
    writeData(E_GroundArea4, E_GroundArea4__data, 39);
    writeData(E_GroundArea5, E_GroundArea5__data, 49);
    writeData(E_GroundArea6, E_GroundArea6__data, 30);
    writeData(E_GroundArea7, E_GroundArea7__data, 29);
    writeData(E_GroundArea8, E_GroundArea8__data, 21);
    writeData(E_GroundArea9, E_GroundArea9__data, 42);
    writeData(E_GroundArea10, E_GroundArea10__data, 1);
    writeData(E_GroundArea11, E_GroundArea11__data, 36);
    writeData(E_GroundArea12, E_GroundArea12__data, 9);
    writeData(E_GroundArea13, E_GroundArea13__data, 37);
    writeData(E_GroundArea14, E_GroundArea14__data, 35);
    writeData(E_GroundArea15, E_GroundArea15__data, 9);
    writeData(E_GroundArea16, E_GroundArea16__data, 1);
    writeData(E_GroundArea17, E_GroundArea17__data, 58);
    writeData(E_GroundArea18, E_GroundArea18__data, 43);
    writeData(E_GroundArea19, E_GroundArea19__data, 46);
    writeData(E_GroundArea20, E_GroundArea20__data, 28);
    writeData(E_GroundArea21, E_GroundArea21__data, 9);
    writeData(E_GroundArea22, E_GroundArea22__data, 37);
    writeData(E_UndergroundArea1, E_UndergroundArea1__data, 45);
    writeData(E_UndergroundArea2, E_UndergroundArea2__data, 46);
    writeData(E_UndergroundArea3, E_UndergroundArea3__data, 45);
    writeData(E_WaterArea1, E_WaterArea1__data, 17);
    writeData(E_WaterArea2, E_WaterArea2__data, 42);
    writeData(E_WaterArea3, E_WaterArea3__data, 20);
    writeData(L_CastleArea1, L_CastleArea1__data, 97);
    writeData(L_CastleArea2, L_CastleArea2__data, 127);
    writeData(L_CastleArea3, L_CastleArea3__data, 115);
    writeData(L_CastleArea4, L_CastleArea4__data, 109);
    writeData(L_CastleArea5, L_CastleArea5__data, 139);
    writeData(L_CastleArea6, L_CastleArea6__data, 113);
    writeData(L_GroundArea1, L_GroundArea1__data, 99);
    writeData(L_GroundArea2, L_GroundArea2__data, 105);
    writeData(L_GroundArea3, L_GroundArea3__data, 83);
    writeData(L_GroundArea4, L_GroundArea4__data, 143);
    writeData(L_GroundArea5, L_GroundArea5__data, 117);
    writeData(L_GroundArea6, L_GroundArea6__data, 101);
    writeData(L_GroundArea7, L_GroundArea7__data, 85);
    writeData(L_GroundArea8, L_GroundArea8__data, 133);
    writeData(L_GroundArea9, L_GroundArea9__data, 101);
    writeData(L_GroundArea10, L_GroundArea10__data, 9);
    writeData(L_GroundArea11, L_GroundArea11__data, 63);
    writeData(L_GroundArea12, L_GroundArea12__data, 21);
    writeData(L_GroundArea13, L_GroundArea13__data, 103);
    writeData(L_GroundArea14, L_GroundArea14__data, 101);
    writeData(L_GroundArea15, L_GroundArea15__data, 115);
    writeData(L_GroundArea16, L_GroundArea16__data, 49);
    writeData(L_GroundArea17, L_GroundArea17__data, 147);
    writeData(L_GroundArea18, L_GroundArea18__data, 115);
    writeData(L_GroundArea19, L_GroundArea19__data, 121);
    writeData(L_GroundArea20, L_GroundArea20__data, 89);
    writeData(L_GroundArea21, L_GroundArea21__data, 43);
    writeData(L_GroundArea22, L_GroundArea22__data, 51);
    writeData(L_UndergroundArea1, L_UndergroundArea1__data, 163);
    writeData(L_UndergroundArea2, L_UndergroundArea2__data, 161);
    writeData(L_UndergroundArea3, L_UndergroundArea3__data, 141);
    writeData(L_WaterArea1, L_WaterArea1__data, 63);
    writeData(L_WaterArea2, L_WaterArea2__data, 123);
    writeData(L_WaterArea3, L_WaterArea3__data, 28);
    writeData(X_SubtracterData, X_SubtracterData__data, 2);
    writeData(OffscrJoypadBitsData, OffscrJoypadBitsData__data, 2);
    writeData(Hidden1UpCoinAmts, Hidden1UpCoinAmts__data, 8);
    writeData(ClimbAdderLow, ClimbAdderLow__data, 4);
    writeData(ClimbAdderHigh, ClimbAdderHigh__data, 4);
    writeData(JumpMForceData, JumpMForceData__data, 7);
    writeData(FallMForceData, FallMForceData__data, 7);
    writeData(PlayerYSpdData, PlayerYSpdData__data, 7);
    writeData(InitMForceData, InitMForceData__data, 7);
    writeData(MaxLeftXSpdData, MaxLeftXSpdData__data, 3);
    writeData(MaxRightXSpdData, MaxRightXSpdData__data, 4);
    writeData(FrictionData, FrictionData__data, 3);
    writeData(Climb_Y_SpeedData, Climb_Y_SpeedData__data, 3);
    writeData(Climb_Y_MForceData, Climb_Y_MForceData__data, 3);
    writeData(PlayerAnimTmrData, PlayerAnimTmrData__data, 3);
    writeData(FireballXSpdData, FireballXSpdData__data, 2);
    writeData(Bubble_MForceData, Bubble_MForceData__data, 2);
    writeData(BubbleTimerData, BubbleTimerData__data, 2);
    writeData(FlagpoleScoreMods, FlagpoleScoreMods__data, 5);
    writeData(FlagpoleScoreDigits, FlagpoleScoreDigits__data, 5);
    writeData(Jumpspring_Y_PosData, Jumpspring_Y_PosData__data, 4);
    writeData(VineHeightData, VineHeightData__data, 2);
    writeData(CannonBitmasks, CannonBitmasks__data, 2);
    writeData(BulletBillXSpdData, BulletBillXSpdData__data, 2);
    writeData(HammerEnemyOfsData, HammerEnemyOfsData__data, 9);
    writeData(HammerXSpdData, HammerXSpdData__data, 2);
    writeData(CoinTallyOffsets, CoinTallyOffsets__data, 2);
    writeData(ScoreOffsets, ScoreOffsets__data, 2);
    writeData(StatusBarNybbles, StatusBarNybbles__data, 2);
    writeData(BlockYPosAdderData, BlockYPosAdderData__data, 2);
    writeData(BrickQBlockMetatiles, BrickQBlockMetatiles__data, 14);
    writeData(MaxSpdBlockData, MaxSpdBlockData__data, 2);
    writeData(LoopCmdWorldNumber, LoopCmdWorldNumber__data, 11);
    writeData(LoopCmdPageNumber, LoopCmdPageNumber__data, 11);
    writeData(LoopCmdYPosition, LoopCmdYPosition__data, 11);
    writeData(NormalXSpdData, NormalXSpdData__data, 2);
    writeData(HBroWalkingTimerData, HBroWalkingTimerData__data, 2);
    writeData(PRDiffAdjustData, PRDiffAdjustData__data, 12);
    writeData(FirebarSpinSpdData, FirebarSpinSpdData__data, 5);
    writeData(FirebarSpinDirData, FirebarSpinDirData__data, 5);
    writeData(FlyCCXPositionData, FlyCCXPositionData__data, 16);
    writeData(FlyCCXSpeedData, FlyCCXSpeedData__data, 12);
    writeData(FlyCCTimerData, FlyCCTimerData__data, 4);
    writeData(FlameYPosData, FlameYPosData__data, 4);
    writeData(FlameYMFAdderData, FlameYMFAdderData__data, 2);
    writeData(FireworksXPosData, FireworksXPosData__data, 6);
    writeData(FireworksYPosData, FireworksYPosData__data, 6);
    writeData(Bitmasks, Bitmasks__data, 8);
    writeData(Enemy17YPosData, Enemy17YPosData__data, 8);
    writeData(SwimCC_IDData, SwimCC_IDData__data, 2);
    writeData(PlatPosDataLow, PlatPosDataLow__data, 3);
    writeData(PlatPosDataHigh, PlatPosDataHigh__data, 3);
    writeData(HammerThrowTmrData, HammerThrowTmrData__data, 2);
    writeData(XSpeedAdderData, XSpeedAdderData__data, 4);
    writeData(RevivedXSpeed, RevivedXSpeed__data, 4);
    writeData(HammerBroJumpLData, HammerBroJumpLData__data, 2);
    writeData(BlooberBitmasks, BlooberBitmasks__data, 2);
    writeData(SwimCCXMoveData, SwimCCXMoveData__data, 4);
    writeData(FirebarPosLookupTbl, FirebarPosLookupTbl__data, 99);
    writeData(FirebarMirrorData, FirebarMirrorData__data, 4);
    writeData(FirebarTblOffsets, FirebarTblOffsets__data, 12);
    writeData(FirebarYPos, FirebarYPos__data, 2);
    writeData(PRandomSubtracter, PRandomSubtracter__data, 5);
    writeData(FlyCCBPriority, FlyCCBPriority__data, 5);
    writeData(LakituDiffAdj, LakituDiffAdj__data, 3);
    writeData(BridgeCollapseData, BridgeCollapseData__data, 15);
    writeData(PRandomRange, PRandomRange__data, 4);
    writeData(FlameTimerData, FlameTimerData__data, 8);
    writeData(StarFlagYPosAdder, StarFlagYPosAdder__data, 4);
    writeData(StarFlagXPosAdder, StarFlagXPosAdder__data, 4);
    writeData(StarFlagTileData, StarFlagTileData__data, 4);
    writeData(BowserIdentities, BowserIdentities__data, 8);
    writeData(ResidualXSpdData, ResidualXSpdData__data, 2);
    writeData(KickedShellXSpdData, KickedShellXSpdData__data, 2);
    writeData(DemotedKoopaXSpdData, DemotedKoopaXSpdData__data, 2);
    writeData(KickedShellPtsData, KickedShellPtsData__data, 3);
    writeData(StompedEnemyPtsData, StompedEnemyPtsData__data, 4);
    writeData(RevivalRateData, RevivalRateData__data, 2);
    writeData(SetBitsMask, SetBitsMask__data, 7);
    writeData(ClearBitsMask, ClearBitsMask__data, 7);
    writeData(PlayerPosSPlatData, PlayerPosSPlatData__data, 2);
    writeData(PlayerBGUpperExtent, PlayerBGUpperExtent__data, 2);
    writeData(AreaChangeTimerData, AreaChangeTimerData__data, 2);
    writeData(ClimbXPosAdder, ClimbXPosAdder__data, 2);
    writeData(ClimbPLocAdder, ClimbPLocAdder__data, 2);
    writeData(FlagpoleYPosData, FlagpoleYPosData__data, 5);
    writeData(SolidMTileUpperExt, SolidMTileUpperExt__data, 4);
    writeData(ClimbMTileUpperExt, ClimbMTileUpperExt__data, 4);
    writeData(EnemyBGCStateData, EnemyBGCStateData__data, 6);
    writeData(EnemyBGCXSpdData, EnemyBGCXSpdData__data, 2);
    writeData(BoundBoxCtrlData, BoundBoxCtrlData__data, 48);
    writeData(BlockBufferAdderData, BlockBufferAdderData__data, 3);
    writeData(BlockBuffer_X_Adder, BlockBuffer_X_Adder__data, 28);
    writeData(BlockBuffer_Y_Adder, BlockBuffer_Y_Adder__data, 28);
    writeData(VineYPosAdder, VineYPosAdder__data, 2);
    writeData(FirstSprXPos, FirstSprXPos__data, 4);
    writeData(FirstSprYPos, FirstSprYPos__data, 4);
    writeData(SecondSprXPos, SecondSprXPos__data, 4);
    writeData(SecondSprYPos, SecondSprYPos__data, 4);
    writeData(FirstSprTilenum, FirstSprTilenum__data, 4);
    writeData(SecondSprTilenum, SecondSprTilenum__data, 4);
    writeData(HammerSprAttrib, HammerSprAttrib__data, 4);
    writeData(FlagpoleScoreNumTiles, FlagpoleScoreNumTiles__data, 10);
    writeData(JumpingCoinTiles, JumpingCoinTiles__data, 4);
    writeData(PowerUpGfxTable, PowerUpGfxTable__data, 16);
    writeData(PowerUpAttributes, PowerUpAttributes__data, 4);
    writeData(EnemyGraphicsTable, EnemyGraphicsTable__data, 258);
    writeData(EnemyGfxTableOffsets, EnemyGfxTableOffsets__data, 27);
    writeData(EnemyAttributeData, EnemyAttributeData__data, 27);
    writeData(EnemyAnimTimingBMask, EnemyAnimTimingBMask__data, 2);
    writeData(JumpspringFrameOffsets, JumpspringFrameOffsets__data, 5);
    writeData(DefaultBlockObjTiles, DefaultBlockObjTiles__data, 4);
    writeData(ExplosionTiles, ExplosionTiles__data, 3);
    writeData(PlayerGfxTblOffsets, PlayerGfxTblOffsets__data, 16);
    writeData(PlayerGraphicsTable, PlayerGraphicsTable__data, 208);
    writeData(SwimKickTileNum, SwimKickTileNum__data, 2);
    writeData(IntermediatePlayerData, IntermediatePlayerData__data, 6);
    writeData(ChangeSizeOffsetAdder, ChangeSizeOffsetAdder__data, 20);
    writeData(ObjOffsetData, ObjOffsetData__data, 3);
    writeData(XOffscreenBitsData, XOffscreenBitsData__data, 16);
    writeData(DefaultXOnscreenOfs, DefaultXOnscreenOfs__data, 3);
    writeData(YOffscreenBitsData, YOffscreenBitsData__data, 9);
    writeData(DefaultYOnscreenOfs, DefaultYOnscreenOfs__data, 3);
    writeData(HighPosUnitData, HighPosUnitData__data, 2);
    writeData(SwimStompEnvelopeData, SwimStompEnvelopeData__data, 14);
    writeData(ExtraLifeFreqData, ExtraLifeFreqData__data, 6);
    writeData(PowerUpGrabFreqData, PowerUpGrabFreqData__data, 30);
    writeData(PUp_VGrow_FreqData, PUp_VGrow_FreqData__data, 32);
    writeData(BrickShatterFreqData, BrickShatterFreqData__data, 16);
    writeData(MusicHeaderData, MusicHeaderData__data, 49);
    writeData(TimeRunningOutHdr, TimeRunningOutHdr__data, 5);
    writeData(Star_CloudHdr, Star_CloudHdr__data, 6);
    writeData(EndOfLevelMusHdr, EndOfLevelMusHdr__data, 5);
    writeData(ResidualHeaderData, ResidualHeaderData__data, 5);
    writeData(UndergroundMusHdr, UndergroundMusHdr__data, 5);
    writeData(SilenceHdr, SilenceHdr__data, 4);
    writeData(CastleMusHdr, CastleMusHdr__data, 5);
    writeData(VictoryMusHdr, VictoryMusHdr__data, 5);
    writeData(GameOverMusHdr, GameOverMusHdr__data, 5);
    writeData(WaterMusHdr, WaterMusHdr__data, 6);
    writeData(WinCastleMusHdr, WinCastleMusHdr__data, 5);
    writeData(GroundLevelPart1Hdr, GroundLevelPart1Hdr__data, 6);
    writeData(GroundLevelPart2AHdr, GroundLevelPart2AHdr__data, 6);
    writeData(GroundLevelPart2BHdr, GroundLevelPart2BHdr__data, 6);
    writeData(GroundLevelPart2CHdr, GroundLevelPart2CHdr__data, 6);
    writeData(GroundLevelPart3AHdr, GroundLevelPart3AHdr__data, 6);
    writeData(GroundLevelPart3BHdr, GroundLevelPart3BHdr__data, 6);
    writeData(GroundLevelLeadInHdr, GroundLevelLeadInHdr__data, 6);
    writeData(GroundLevelPart4AHdr, GroundLevelPart4AHdr__data, 6);
    writeData(GroundLevelPart4BHdr, GroundLevelPart4BHdr__data, 6);
    writeData(GroundLevelPart4CHdr, GroundLevelPart4CHdr__data, 6);
    writeData(DeathMusHdr, DeathMusHdr__data, 6);
    writeData(Star_CloudMData, Star_CloudMData__data, 73);
    writeData(GroundM_P1Data, GroundM_P1Data__data, 27);
    writeData(SilenceData, SilenceData__data, 45);
    writeData(GroundM_P2AData, GroundM_P2AData__data, 44);
    writeData(GroundM_P2BData, GroundM_P2BData__data, 40);
    writeData(GroundM_P2CData, GroundM_P2CData__data, 37);
    writeData(GroundM_P3AData, GroundM_P3AData__data, 25);
    writeData(GroundM_P3BData, GroundM_P3BData__data, 30);
    writeData(GroundMLdInData, GroundMLdInData__data, 44);
    writeData(GroundM_P4AData, GroundM_P4AData__data, 38);
    writeData(GroundM_P4BData, GroundM_P4BData__data, 39);
    writeData(DeathMusData, DeathMusData__data, 2);
    writeData(GroundM_P4CData, GroundM_P4CData__data, 48);
    writeData(CastleMusData, CastleMusData__data, 161);
    writeData(GameOverMusData, GameOverMusData__data, 45);
    writeData(TimeRunOutMusData, TimeRunOutMusData__data, 62);
    writeData(WinLevelMusData, WinLevelMusData__data, 97);
    writeData(UndergroundMusData, UndergroundMusData__data, 65);
    writeData(WaterMusData, WaterMusData__data, 255);
    writeData(EndOfCastleMusData, EndOfCastleMusData__data, 119);
    writeData(VictoryMusData, VictoryMusData__data, 56);
    writeData(FreqRegLookupTbl, FreqRegLookupTbl__data, 102);
    writeData(MusicLengthLookupTbl, MusicLengthLookupTbl__data, 48);
    writeData(EndOfCastleMusicEnvData, EndOfCastleMusicEnvData__data, 4);
    writeData(AreaMusicEnvData, AreaMusicEnvData__data, 8);
    writeData(WaterEventMusEnvData, WaterEventMusEnvData__data, 40);
    writeData(BowserFlameEnvData, BowserFlameEnvData__data, 32);
    writeData(BrickShatterEnvData, BrickShatterEnvData__data, 19);
}

void code(int mode)
{
    switch(mode)
    {
    case 0:
        loadConstantData();
        goto Start;
    case 1:
        goto NonMaskableInterrupt;
    }
Start:
    a = BOOST_BINARY(00010000);
    writeData(PPU_CTRL_REG1, a);
    x = 0xff;
    s = x;
VBlank1:
    a = M(PPU_STATUS);
    if (!n)
        goto VBlank1;
VBlank2:
    a = M(PPU_STATUS);
    if (!n)
        goto VBlank2;
    y = ColdBootOffset;
    x = 0x05;
WBootCheck:
    a = M(TopScoreDisplay + x);
    compare(a, 10);
    if (c)
        goto ColdBoot;
    --x;
    if (!n)
        goto WBootCheck;
    a = M(WarmBootValidation);
    compare(a, 0xa5);
    if (!z)
        goto ColdBoot;
    y = WarmBootOffset;
ColdBoot:
    JSR(InitializeMemory, 0)
    writeData(SND_DELTA_REG + 1, a);
    writeData(OperMode, a);
    a = 0xa5;
    writeData(WarmBootValidation, a);
    writeData(PseudoRandomBitReg, a);
    a = BOOST_BINARY(00001111);
    writeData(SND_MASTERCTRL_REG, a);
    a = BOOST_BINARY(00000110);
    writeData(PPU_CTRL_REG2, a);
    JSR(MoveAllSpritesOffscreen, 1)
    JSR(InitializeNameTables, 2)
    ++M(DisableScreenFlag);
    a = M(Mirror_PPU_CTRL_REG1);
    a |= BOOST_BINARY(10000000);
    JSR(WritePPUReg1, 3)
EndlessLoop:
    return; // Initialization complete

//---------------------------------------------------------------------

NonMaskableInterrupt:
    a = M(Mirror_PPU_CTRL_REG1);
    a &= BOOST_BINARY(01111111);
    writeData(Mirror_PPU_CTRL_REG1, a);
    a &= BOOST_BINARY(01111110);
    writeData(PPU_CTRL_REG1, a);
    a = M(Mirror_PPU_CTRL_REG2);
    a &= BOOST_BINARY(11100110);
    y = M(DisableScreenFlag);
    if (!z)
        goto ScreenOff;
    a = M(Mirror_PPU_CTRL_REG2);
    a |= BOOST_BINARY(00011110);
ScreenOff:
    writeData(Mirror_PPU_CTRL_REG2, a);
    a &= BOOST_BINARY(11100111);
    writeData(PPU_CTRL_REG2, a);
    x = M(PPU_STATUS);
    a = 0x00;
    JSR(InitScroll, 4)
    writeData(PPU_SPR_ADDR, a);
    a = 0x02;
    writeData(SPR_DMA, a);
    x = M(VRAM_Buffer_AddrCtrl);
    a = M(VRAM_AddrTable_Low + x);
    writeData(0x00, a);
    a = M(VRAM_AddrTable_High + x);
    writeData(0x01, a);
    JSR(UpdateScreen, 5)
    y = 0x00;
    x = M(VRAM_Buffer_AddrCtrl);
    compare(x, 0x06);
    if (!z)
        goto InitBuffer;
    ++y;
InitBuffer:
    x = M(VRAM_Buffer_Offset + y);
    a = 0x00;
    writeData(VRAM_Buffer1_Offset + x, a);
    writeData(VRAM_Buffer1 + x, a);
    writeData(VRAM_Buffer_AddrCtrl, a);
    a = M(Mirror_PPU_CTRL_REG2);
    writeData(PPU_CTRL_REG2, a);
    JSR(SoundEngine, 6)
    JSR(ReadJoypads, 7)
    JSR(PauseRoutine, 8)
    JSR(UpdateTopScore, 9)
    a = M(GamePauseStatus);
    a >>= 1;
    if (c)
        goto PauseSkip;
    a = M(TimerControl);
    if (z)
        goto DecTimers;
    --M(TimerControl);
    if (!z)
        goto NoDecTimers;
DecTimers:
    x = 0x14;
    --M(IntervalTimerControl);
    if (!n)
        goto DecTimersLoop;
    a = 0x14;
    writeData(IntervalTimerControl, a);
    x = 0x23;
DecTimersLoop:
    a = M(Timers + x);
    if (z)
        goto SkipExpTimer;
    --M(Timers + x);
SkipExpTimer:
    --x;
    if (!n)
        goto DecTimersLoop;
NoDecTimers:
    ++M(FrameCounter);
PauseSkip:
    x = 0x00;
    y = 0x07;
    a = M(PseudoRandomBitReg);
    a &= BOOST_BINARY(00000010);
    writeData(0x00, a);
    a = M(PseudoRandomBitReg + 1);
    a &= BOOST_BINARY(00000010);
    a ^= M(0x00);
    c = 0;
    if (z)
        goto RotPRandomBit;
    c = 1;
RotPRandomBit:
    M(PseudoRandomBitReg + x).ror();
    ++x;
    --y;
    if (!z)
        goto RotPRandomBit;
    a = M(Sprite0HitDetectFlag);
    if (z)
        goto SkipSprite0;
Sprite0Clr:
    a = M(PPU_STATUS);
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto Sprite0Clr;
    a = M(GamePauseStatus);
    a >>= 1;
    if (c)
        goto Sprite0Hit;
    JSR(MoveSpritesOffscreen, 10)
    JSR(SpriteShuffler, 11)
Sprite0Hit:
    a = M(PPU_STATUS);
    a &= BOOST_BINARY(01000000);
    if (z)
        goto Sprite0Hit;
    y = 0x14;
HBlankDelay:
    --y;
    if (!z)
        goto HBlankDelay;
SkipSprite0:
    a = M(HorizontalScroll);
    writeData(PPU_SCROLL_REG, a);
    a = M(VerticalScroll);
    writeData(PPU_SCROLL_REG, a);
    a = M(Mirror_PPU_CTRL_REG1);
    pha();
    writeData(PPU_CTRL_REG1, a);
    a = M(GamePauseStatus);
    a >>= 1;
    if (c)
        goto SkipMainOper;
    JSR(OperModeExecutionTree, 12)
SkipMainOper:
    a = M(PPU_STATUS);
    pla();
    a |= BOOST_BINARY(10000000);
    writeData(PPU_CTRL_REG1, a);
    return; // RTI

//---------------------------------------------------------------------

PauseRoutine:
    a = M(OperMode);
    compare(a, VictoryModeValue);
    if (z)
        goto ChkPauseTimer;
    compare(a, GameModeValue);
    if (!z)
        goto ExitPause;
    a = M(OperMode_Task);
    compare(a, 0x03);
    if (!z)
        goto ExitPause;
ChkPauseTimer:
    a = M(GamePauseTimer);
    if (z)
        goto ChkStart;
    --M(GamePauseTimer);
    goto Return;

//---------------------------------------------------------------------

ChkStart:
    a = M(SavedJoypad1Bits);
    a &= Start_Button;
    if (z)
        goto ClrPauseTimer;
    a = M(GamePauseStatus);
    a &= BOOST_BINARY(10000000);
    if (!z)
        goto ExitPause;
    a = 0x2b;
    writeData(GamePauseTimer, a);
    a = M(GamePauseStatus);
    y = a;
    ++y;
    writeData(PauseSoundQueue, y);
    a ^= BOOST_BINARY(00000001);
    a |= BOOST_BINARY(10000000);
    if (!z)
        goto SetPause;
ClrPauseTimer:
    a = M(GamePauseStatus);
    a &= BOOST_BINARY(01111111);
SetPause:
    writeData(GamePauseStatus, a);
ExitPause:
    goto Return;

//---------------------------------------------------------------------

SpriteShuffler:
    y = M(AreaType);
    a = 0x28;
    writeData(0x00, a);
    x = 0x0e;
ShuffleLoop:
    a = M(SprDataOffset + x);
    compare(a, M(0x00));
    if (!c)
        goto NextSprOffset;
    y = M(SprShuffleAmtOffset);
    c = 0;
    a += M(SprShuffleAmt + y);
    if (!c)
        goto StrSprOffset;
    c = 0;
    a += M(0x00);
StrSprOffset:
    writeData(SprDataOffset + x, a);
NextSprOffset:
    --x;
    if (!n)
        goto ShuffleLoop;
    x = M(SprShuffleAmtOffset);
    ++x;
    compare(x, 0x03);
    if (!z)
        goto SetAmtOffset;
    x = 0x00;
SetAmtOffset:
    writeData(SprShuffleAmtOffset, x);
    x = 0x08;
    y = 0x02;
SetMiscOffset:
    a = M(SprDataOffset + 5 + y);
    writeData(Misc_SprDataOffset - 2 + x, a);
    c = 0;
    a += 0x08;
    writeData(Misc_SprDataOffset - 1 + x, a);
    c = 0;
    a += 0x08;
    writeData(Misc_SprDataOffset + x, a);
    --x;
    --x;
    --x;
    --y;
    if (!n)
        goto SetMiscOffset;
    goto Return;

//---------------------------------------------------------------------

OperModeExecutionTree:
    a = M(OperMode);
    switch(a)
        {
    case 0:
        goto TitleScreenMode;
    case 1:
        goto GameMode;
    case 2:
        goto VictoryMode;
    case 3:
        goto GameOverMode;
    }
MoveAllSpritesOffscreen:
    y = 0x00;
    goto Skip_0;
MoveSpritesOffscreen:
    y = 0x04;
Skip_0:
    a = 0xf8;
SprInitLoop:
    writeData(Sprite_Y_Position + y, a);
    ++y;
    ++y;
    ++y;
    ++y;
    if (!z)
        goto SprInitLoop;
    goto Return;

//---------------------------------------------------------------------

TitleScreenMode:
    a = M(OperMode_Task);
    switch(a)
        {
    case 0:
        goto InitializeGame;
    case 1:
        goto ScreenRoutines;
    case 2:
        goto PrimaryGameSetup;
    case 3:
        goto GameMenuRoutine;
    }
GameMenuRoutine:
    y = 0x00;
    a = M(SavedJoypad1Bits);
    a |= M(SavedJoypad2Bits);
    compare(a, Start_Button);
    if (z)
        goto StartGame;
    compare(a, A_Button + Start_Button);
    if (!z)
        goto ChkSelect;
StartGame:
    goto ChkContinue;
ChkSelect:
    compare(a, Select_Button);
    if (z)
        goto SelectBLogic;
    x = M(DemoTimer);
    if (!z)
        goto ChkWorldSel;
    writeData(SelectTimer, a);
    JSR(DemoEngine, 13)
    if (c)
        goto ResetTitle;
    goto RunDemo;
ChkWorldSel:
    x = M(WorldSelectEnableFlag);
    if (z)
        goto NullJoypad;
    compare(a, B_Button);
    if (!z)
        goto NullJoypad;
    ++y;
SelectBLogic:
    a = M(DemoTimer);
    if (z)
        goto ResetTitle;
    a = 0x18;
    writeData(DemoTimer, a);
    a = M(SelectTimer);
    if (!z)
        goto NullJoypad;
    a = 0x10;
    writeData(SelectTimer, a);
    compare(y, 0x01);
    if (z)
        goto IncWorldSel;
    a = M(NumberOfPlayers);
    a ^= BOOST_BINARY(00000001);
    writeData(NumberOfPlayers, a);
    JSR(DrawMushroomIcon, 14)
    goto NullJoypad;
IncWorldSel:
    x = M(WorldSelectNumber);
    ++x;
    a = x;
    a &= BOOST_BINARY(00000111);
    writeData(WorldSelectNumber, a);
    JSR(GoContinue, 15)
UpdateShroom:
    a = M(WSelectBufferTemplate + x);
    writeData(VRAM_Buffer1 - 1 + x, a);
    ++x;
    compare(x, 0x06);
    if (n)
        goto UpdateShroom;
    y = M(WorldNumber);
    ++y;
    writeData(VRAM_Buffer1 + 3, y);
NullJoypad:
    a = 0x00;
    writeData(SavedJoypad1Bits, a);
RunDemo:
    JSR(GameCoreRoutine, 16)
    a = M(GameEngineSubroutine);
    compare(a, 0x06);
    if (!z)
        goto ExitMenu;
ResetTitle:
    a = 0x00;
    writeData(OperMode, a);
    writeData(OperMode_Task, a);
    writeData(Sprite0HitDetectFlag, a);
    ++M(DisableScreenFlag);
    goto Return;

//---------------------------------------------------------------------

ChkContinue:
    y = M(DemoTimer);
    if (z)
        goto ResetTitle;
    a <<= 1;
    if (!c)
        goto StartWorld1;
    a = M(ContinueWorld);
    JSR(GoContinue, 17)
StartWorld1:
    JSR(LoadAreaPointer, 18)
    ++M(Hidden1UpFlag);
    ++M(OffScr_Hidden1UpFlag);
    ++M(FetchNewGameTimerFlag);
    ++M(OperMode);
    a = M(WorldSelectEnableFlag);
    writeData(PrimaryHardMode, a);
    a = 0x00;
    writeData(OperMode_Task, a);
    writeData(DemoTimer, a);
    x = 0x17;
    a = 0x00;
InitScores:
    writeData(ScoreAndCoinDisplay + x, a);
    --x;
    if (!n)
        goto InitScores;
ExitMenu:
    goto Return;

//---------------------------------------------------------------------

GoContinue:
    writeData(WorldNumber, a);
    writeData(OffScr_WorldNumber, a);
    x = 0x00;
    writeData(AreaNumber, x);
    writeData(OffScr_AreaNumber, x);
    goto Return;

//---------------------------------------------------------------------

DrawMushroomIcon:
    y = 0x07;
IconDataRead:
    a = M(MushroomIconData + y);
    writeData(VRAM_Buffer1 - 1 + y, a);
    --y;
    if (!n)
        goto IconDataRead;
    a = M(NumberOfPlayers);
    if (z)
        goto ExitIcon;
    a = 0x24;
    writeData(VRAM_Buffer1 + 3, a);
    a = 0xce;
    writeData(VRAM_Buffer1 + 5, a);
ExitIcon:
    goto Return;

//---------------------------------------------------------------------

DemoEngine:
    x = M(DemoAction);
    a = M(DemoActionTimer);
    if (!z)
        goto DoAction;
    ++x;
    ++M(DemoAction);
    c = 1;
    a = M(DemoTimingData - 1 + x);
    writeData(DemoActionTimer, a);
    if (z)
        goto DemoOver;
DoAction:
    a = M(DemoActionData - 1 + x);
    writeData(SavedJoypad1Bits, a);
    --M(DemoActionTimer);
    c = 0;
DemoOver:
    goto Return;

//---------------------------------------------------------------------

VictoryMode:
    JSR(VictoryModeSubroutines, 19)
    a = M(OperMode_Task);
    if (z)
        goto AutoPlayer;
    x = 0x00;
    writeData(ObjectOffset, x);
    JSR(EnemiesAndLoopsCore, 20)
AutoPlayer:
    JSR(RelativePlayerPosition, 21)
    goto PlayerGfxHandler;
VictoryModeSubroutines:
    a = M(OperMode_Task);
    switch(a)
        {
    case 0:
        goto BridgeCollapse;
    case 1:
        goto SetupVictoryMode;
    case 2:
        goto PlayerVictoryWalk;
    case 3:
        goto PrintVictoryMessages;
    case 4:
        goto PlayerEndWorld;
    }
SetupVictoryMode:
    x = M(ScreenRight_PageLoc);
    ++x;
    writeData(DestinationPageLoc, x);
    a = EndOfCastleMusic;
    writeData(EventMusicQueue, a);
    goto IncModeTask_B;
PlayerVictoryWalk:
    y = 0x00;
    writeData(VictoryWalkControl, y);
    a = M(Player_PageLoc);
    compare(a, M(DestinationPageLoc));
    if (!z)
        goto PerformWalk;
    a = M(Player_X_Position);
    compare(a, 0x60);
    if (c)
        goto DontWalk;
PerformWalk:
    ++M(VictoryWalkControl);
    ++y;
DontWalk:
    a = y;
    JSR(AutoControlPlayer, 22)
    a = M(ScreenLeft_PageLoc);
    compare(a, M(DestinationPageLoc));
    if (z)
        goto ExitVWalk;
    a = M(ScrollFractional);
    c = 0;
    a += 0x80;
    writeData(ScrollFractional, a);
    a = 0x01;
    a += 0x00;
    y = a;
    JSR(ScrollScreen, 23)
    JSR(UpdScrollVar, 24)
    ++M(VictoryWalkControl);
ExitVWalk:
    a = M(VictoryWalkControl);
    if (z)
        goto IncModeTask_A;
    goto Return;

//---------------------------------------------------------------------

PrintVictoryMessages:
    a = M(SecondaryMsgCounter);
    if (!z)
        goto IncMsgCounter;
    a = M(PrimaryMsgCounter);
    if (z)
        goto ThankPlayer;
    compare(a, 0x09);
    if (c)
        goto IncMsgCounter;
    y = M(WorldNumber);
    compare(y, World8);
    if (!z)
        goto MRetainerMsg;
    compare(a, 0x03);
    if (!c)
        goto IncMsgCounter;
    a -= 0x01;
    goto ThankPlayer;
MRetainerMsg:
    compare(a, 0x02);
    if (!c)
        goto IncMsgCounter;
ThankPlayer:
    y = a;
    if (!z)
        goto SecondPartMsg;
    a = M(CurrentPlayer);
    if (z)
        goto EvalForMusic;
    ++y;
    if (!z)
        goto EvalForMusic;
SecondPartMsg:
    ++y;
    a = M(WorldNumber);
    compare(a, World8);
    if (z)
        goto EvalForMusic;
    --y;
    compare(y, 0x04);
    if (c)
        goto SetEndTimer;
    compare(y, 0x03);
    if (c)
        goto IncMsgCounter;
EvalForMusic:
    compare(y, 0x03);
    if (!z)
        goto PrintMsg;
    a = VictoryMusic;
    writeData(EventMusicQueue, a);
PrintMsg:
    a = y;
    c = 0;
    a += 0x0c;
    writeData(VRAM_Buffer_AddrCtrl, a);
IncMsgCounter:
    a = M(SecondaryMsgCounter);
    c = 0;
    a += 0x04;
    writeData(SecondaryMsgCounter, a);
    a = M(PrimaryMsgCounter);
    a += 0x00;
    writeData(PrimaryMsgCounter, a);
    compare(a, 0x07);
SetEndTimer:
    if (!c)
        goto ExitMsgs;
    a = 0x06;
    writeData(WorldEndTimer, a);
IncModeTask_A:
    ++M(OperMode_Task);
ExitMsgs:
    goto Return;

//---------------------------------------------------------------------

PlayerEndWorld:
    a = M(WorldEndTimer);
    if (!z)
        goto EndExitOne;
    y = M(WorldNumber);
    compare(y, World8);
    if (c)
        goto EndChkBButton;
    a = 0x00;
    writeData(AreaNumber, a);
    writeData(LevelNumber, a);
    writeData(OperMode_Task, a);
    ++M(WorldNumber);
    JSR(LoadAreaPointer, 25)
    ++M(FetchNewGameTimerFlag);
    a = GameModeValue;
    writeData(OperMode, a);
EndExitOne:
    goto Return;

//---------------------------------------------------------------------

EndChkBButton:
    a = M(SavedJoypad1Bits);
    a |= M(SavedJoypad2Bits);
    a &= B_Button;
    if (z)
        goto EndExitTwo;
    a = 0x01;
    writeData(WorldSelectEnableFlag, a);
    a = 0xff;
    writeData(NumberofLives, a);
    JSR(TerminateGame, 26)
EndExitTwo:
    goto Return;

//---------------------------------------------------------------------

FloateyNumbersRoutine:
    a = M(FloateyNum_Control + x);
    if (z)
        goto EndExitOne;
    compare(a, 0x0b);
    if (!c)
        goto ChkNumTimer;
    a = 0x0b;
    writeData(FloateyNum_Control + x, a);
ChkNumTimer:
    y = a;
    a = M(FloateyNum_Timer + x);
    if (!z)
        goto DecNumTimer;
    writeData(FloateyNum_Control + x, a);
    goto Return;

//---------------------------------------------------------------------

DecNumTimer:
    --M(FloateyNum_Timer + x);
    compare(a, 0x2b);
    if (!z)
        goto ChkTallEnemy;
    compare(y, 0x0b);
    if (!z)
        goto LoadNumTiles;
    ++M(NumberofLives);
    a = Sfx_ExtraLife;
    writeData(Square2SoundQueue, a);
LoadNumTiles:
    a = M(ScoreUpdateData + y);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    x = a;
    a = M(ScoreUpdateData + y);
    a &= BOOST_BINARY(00001111);
    writeData(DigitModifier + x, a);
    JSR(AddToScore, 27)
ChkTallEnemy:
    y = M(Enemy_SprDataOffset + x);
    a = M(Enemy_ID + x);
    compare(a, Spiny);
    if (z)
        goto FloateyPart;
    compare(a, PiranhaPlant);
    if (z)
        goto FloateyPart;
    compare(a, HammerBro);
    if (z)
        goto GetAltOffset;
    compare(a, GreyCheepCheep);
    if (z)
        goto FloateyPart;
    compare(a, RedCheepCheep);
    if (z)
        goto FloateyPart;
    compare(a, TallEnemy);
    if (c)
        goto GetAltOffset;
    a = M(Enemy_State + x);
    compare(a, 0x02);
    if (c)
        goto FloateyPart;
GetAltOffset:
    x = M(SprDataOffset_Ctrl);
    y = M(Alt_SprDataOffset + x);
    x = M(ObjectOffset);
FloateyPart:
    a = M(FloateyNum_Y_Pos + x);
    compare(a, 0x18);
    if (!c)
        goto SetupNumSpr;
    a -= 0x01;
    writeData(FloateyNum_Y_Pos + x, a);
SetupNumSpr:
    a = M(FloateyNum_Y_Pos + x);
    a -= 0x08;
    JSR(DumpTwoSpr, 28)
    a = M(FloateyNum_X_Pos + x);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 4 + y, a);
    a = 0x02;
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    a = M(FloateyNum_Control + x);
    a <<= 1;
    x = a;
    a = M(FloateyNumTileData + x);
    writeData(Sprite_Tilenumber + y, a);
    a = M(FloateyNumTileData + 1 + x);
    writeData(Sprite_Tilenumber + 4 + y, a);
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ScreenRoutines:
    a = M(ScreenRoutineTask);
    switch(a)
        {
    case 0:
        goto InitScreen;
    case 1:
        goto SetupIntermediate;
    case 2:
        goto WriteTopStatusLine;
    case 3:
        goto WriteBottomStatusLine;
    case 4:
        goto DisplayTimeUp;
    case 5:
        goto ResetSpritesAndScreenTimer;
    case 6:
        goto DisplayIntermediate;
    case 7:
        goto ResetSpritesAndScreenTimer;
    case 8:
        goto AreaParserTaskControl;
    case 9:
        goto GetAreaPalette;
    case 10:
        goto GetBackgroundColor;
    case 11:
        goto GetAlternatePalette1;
    case 12:
        goto DrawTitleScreen;
    case 13:
        goto ClearBuffersDrawIcon;
    case 14:
        goto WriteTopScore;
    }
InitScreen:
    JSR(MoveAllSpritesOffscreen, 29)
    JSR(InitializeNameTables, 30)
    a = M(OperMode);
    if (z)
        goto NextSubtask;
    x = 0x03;
    goto SetVRAMAddr_A;
SetupIntermediate:
    a = M(BackgroundColorCtrl);
    pha();
    a = M(PlayerStatus);
    pha();
    a = 0x00;
    writeData(PlayerStatus, a);
    a = 0x02;
    writeData(BackgroundColorCtrl, a);
    JSR(GetPlayerColors, 31)
    pla();
    writeData(PlayerStatus, a);
    pla();
    writeData(BackgroundColorCtrl, a);
    goto IncSubtask;
GetAreaPalette:
    y = M(AreaType);
    x = M(AreaPalette + y);
SetVRAMAddr_A:
    writeData(VRAM_Buffer_AddrCtrl, x);
NextSubtask:
    goto IncSubtask;
GetBackgroundColor:
    y = M(BackgroundColorCtrl);
    if (z)
        goto NoBGColor;
    a = M(BGColorCtrl_Addr - 4 + y);
    writeData(VRAM_Buffer_AddrCtrl, a);
NoBGColor:
    ++M(ScreenRoutineTask);
GetPlayerColors:
    x = M(VRAM_Buffer1_Offset);
    y = 0x00;
    a = M(CurrentPlayer);
    if (z)
        goto ChkFiery;
    y = 0x04;
ChkFiery:
    a = M(PlayerStatus);
    compare(a, 0x02);
    if (!z)
        goto StartClrGet;
    y = 0x08;
StartClrGet:
    a = 0x03;
    writeData(0x00, a);
ClrGetLoop:
    a = M(PlayerColors + y);
    writeData(VRAM_Buffer1 + 3 + x, a);
    ++y;
    ++x;
    --M(0x00);
    if (!n)
        goto ClrGetLoop;
    x = M(VRAM_Buffer1_Offset);
    y = M(BackgroundColorCtrl);
    if (!z)
        goto SetBGColor;
    y = M(AreaType);
SetBGColor:
    a = M(BackgroundColors + y);
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = 0x3f;
    writeData(VRAM_Buffer1 + x, a);
    a = 0x10;
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = 0x04;
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = 0x00;
    writeData(VRAM_Buffer1 + 7 + x, a);
    a = x;
    c = 0;
    a += 0x07;
SetVRAMOffset:
    writeData(VRAM_Buffer1_Offset, a);
    goto Return;

//---------------------------------------------------------------------

GetAlternatePalette1:
    a = M(AreaStyle);
    compare(a, 0x01);
    if (!z)
        goto NoAltPal;
    a = 0x0b;
SetVRAMAddr_B:
    writeData(VRAM_Buffer_AddrCtrl, a);
NoAltPal:
    goto IncSubtask;
WriteTopStatusLine:
    a = 0x00;
    JSR(WriteGameText, 32)
    goto IncSubtask;
WriteBottomStatusLine:
    JSR(GetSBNybbles, 33)
    x = M(VRAM_Buffer1_Offset);
    a = 0x20;
    writeData(VRAM_Buffer1 + x, a);
    a = 0x73;
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = 0x03;
    writeData(VRAM_Buffer1 + 2 + x, a);
    y = M(WorldNumber);
    ++y;
    a = y;
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = 0x28;
    writeData(VRAM_Buffer1 + 4 + x, a);
    y = M(LevelNumber);
    ++y;
    a = y;
    writeData(VRAM_Buffer1 + 5 + x, a);
    a = 0x00;
    writeData(VRAM_Buffer1 + 6 + x, a);
    a = x;
    c = 0;
    a += 0x06;
    writeData(VRAM_Buffer1_Offset, a);
    goto IncSubtask;
DisplayTimeUp:
    a = M(GameTimerExpiredFlag);
    if (z)
        goto NoTimeUp;
    a = 0x00;
    writeData(GameTimerExpiredFlag, a);
    a = 0x02;
    goto OutputInter;
NoTimeUp:
    ++M(ScreenRoutineTask);
    goto IncSubtask;
DisplayIntermediate:
    a = M(OperMode);
    if (z)
        goto NoInter;
    compare(a, GameOverModeValue);
    if (z)
        goto GameOverInter;
    a = M(AltEntranceControl);
    if (!z)
        goto NoInter;
    y = M(AreaType);
    compare(y, 0x03);
    if (z)
        goto PlayerInter;
    a = M(DisableIntermediate);
    if (!z)
        goto NoInter;
PlayerInter:
    JSR(DrawPlayer_Intermediate, 34)
    a = 0x01;
OutputInter:
    JSR(WriteGameText, 35)
    JSR(ResetScreenTimer, 36)
    a = 0x00;
    writeData(DisableScreenFlag, a);
    goto Return;

//---------------------------------------------------------------------

GameOverInter:
    a = 0x12;
    writeData(ScreenTimer, a);
    a = 0x03;
    JSR(WriteGameText, 37)
    goto IncModeTask_B;
NoInter:
    a = 0x08;
    writeData(ScreenRoutineTask, a);
    goto Return;

//---------------------------------------------------------------------

AreaParserTaskControl:
    ++M(DisableScreenFlag);
TaskLoop:
    JSR(AreaParserTaskHandler, 38)
    a = M(AreaParserTaskNum);
    if (!z)
        goto TaskLoop;
    --M(ColumnSets);
    if (!n)
        goto OutputCol;
    ++M(ScreenRoutineTask);
OutputCol:
    a = 0x06;
    writeData(VRAM_Buffer_AddrCtrl, a);
    goto Return;

//---------------------------------------------------------------------

DrawTitleScreen:
    a = M(OperMode);
    if (!z)
        goto IncModeTask_B;
    a = HIBYTE(TitleScreenDataOffset);
    writeData(PPU_ADDRESS, a);
    a = LOBYTE(TitleScreenDataOffset);
    writeData(PPU_ADDRESS, a);
    a = 0x03;
    writeData(0x01, a);
    y = 0x00;
    writeData(0x00, y);
    a = M(PPU_DATA);
OutputTScr:
    a = M(PPU_DATA);
    writeData(W(0x00) + y, a);
    ++y;
    if (!z)
        goto ChkHiByte;
    ++M(0x01);
ChkHiByte:
    a = M(0x01);
    compare(a, 0x04);
    if (!z)
        goto OutputTScr;
    compare(y, 0x3a);
    if (!c)
        goto OutputTScr;
    a = 0x05;
    goto SetVRAMAddr_B;
ClearBuffersDrawIcon:
    a = M(OperMode);
    if (!z)
        goto IncModeTask_B;
    x = 0x00;
TScrClear:
    writeData(VRAM_Buffer1 - 1 + x, a);
    writeData(VRAM_Buffer1 - 1 + 0x100 + x, a);
    --x;
    if (!z)
        goto TScrClear;
    JSR(DrawMushroomIcon, 39)
IncSubtask:
    ++M(ScreenRoutineTask);
    goto Return;

//---------------------------------------------------------------------

WriteTopScore:
    a = 0xfa;
    JSR(UpdateNumber, 40)
IncModeTask_B:
    ++M(OperMode_Task);
    goto Return;

//---------------------------------------------------------------------

WriteGameText:
    pha();
    a <<= 1;
    y = a;
    compare(y, 0x04);
    if (!c)
        goto LdGameText;
    compare(y, 0x08);
    if (!c)
        goto Chk2Players;
    y = 0x08;
Chk2Players:
    a = M(NumberOfPlayers);
    if (!z)
        goto LdGameText;
    ++y;
LdGameText:
    x = M(GameTextOffsets + y);
    y = 0x00;
GameTextLoop:
    a = M(GameText + x);
    compare(a, 0xff);
    if (z)
        goto EndGameText;
    writeData(VRAM_Buffer1 + y, a);
    ++x;
    ++y;
    if (!z)
        goto GameTextLoop;
EndGameText:
    a = 0x00;
    writeData(VRAM_Buffer1 + y, a);
    pla();
    x = a;
    compare(a, 0x04);
    if (c)
        goto PrintWarpZoneNumbers;
    --x;
    if (!z)
        goto CheckPlayerName;
    a = M(NumberofLives);
    c = 0;
    a += 0x01;
    compare(a, 10);
    if (!c)
        goto PutLives;
    a -= 10;
    y = 0x9f;
    writeData(VRAM_Buffer1 + 7, y);
PutLives:
    writeData(VRAM_Buffer1 + 8, a);
    y = M(WorldNumber);
    ++y;
    writeData(VRAM_Buffer1 + 19, y);
    y = M(LevelNumber);
    ++y;
    writeData(VRAM_Buffer1 + 21, y);
    goto Return;

//---------------------------------------------------------------------

CheckPlayerName:
    a = M(NumberOfPlayers);
    if (z)
        goto ExitChkName;
    a = M(CurrentPlayer);
    --x;
    if (!z)
        goto ChkLuigi;
    y = M(OperMode);
    compare(y, GameOverModeValue);
    if (z)
        goto ChkLuigi;
    a ^= BOOST_BINARY(00000001);
ChkLuigi:
    a >>= 1;
    if (!c)
        goto ExitChkName;
    y = 0x04;
NameLoop:
    a = M(LuigiName + y);
    writeData(VRAM_Buffer1 + 3 + y, a);
    --y;
    if (!n)
        goto NameLoop;
ExitChkName:
    goto Return;

//---------------------------------------------------------------------

PrintWarpZoneNumbers:
    a -= 0x04;
    a <<= 1;
    a <<= 1;
    x = a;
    y = 0x00;
WarpNumLoop:
    a = M(WarpZoneNumbers + x);
    writeData(VRAM_Buffer1 + 27 + y, a);
    ++x;
    ++y;
    ++y;
    ++y;
    ++y;
    compare(y, 0x0c);
    if (!c)
        goto WarpNumLoop;
    a = 0x2c;
    goto SetVRAMOffset;
ResetSpritesAndScreenTimer:
    a = M(ScreenTimer);
    if (!z)
        goto NoReset;
    JSR(MoveAllSpritesOffscreen, 41)
ResetScreenTimer:
    a = 0x07;
    writeData(ScreenTimer, a);
    ++M(ScreenRoutineTask);
NoReset:
    goto Return;

//---------------------------------------------------------------------

RenderAreaGraphics:
    a = M(CurrentColumnPos);
    a &= 0x01;
    writeData(0x05, a);
    y = M(VRAM_Buffer2_Offset);
    writeData(0x00, y);
    a = M(CurrentNTAddr_Low);
    writeData(VRAM_Buffer2 + 1 + y, a);
    a = M(CurrentNTAddr_High);
    writeData(VRAM_Buffer2 + y, a);
    a = 0x9a;
    writeData(VRAM_Buffer2 + 2 + y, a);
    a = 0x00;
    writeData(0x04, a);
    x = a;
DrawMTLoop:
    writeData(0x01, x);
    a = M(MetatileBuffer + x);
    a &= BOOST_BINARY(11000000);
    writeData(0x03, a);
    a <<= 1;
    a.rol();
    a.rol();
    y = a;
    a = M(MetatileGraphics_Low + y);
    writeData(0x06, a);
    a = M(MetatileGraphics_High + y);
    writeData(0x07, a);
    a = M(MetatileBuffer + x);
    a <<= 1;
    a <<= 1;
    writeData(0x02, a);
    a = M(AreaParserTaskNum);
    a &= BOOST_BINARY(00000001);
    a ^= BOOST_BINARY(00000001);
    a <<= 1;
    a += M(0x02);
    y = a;
    x = M(0x00);
    a = M(W(0x06) + y);
    writeData(VRAM_Buffer2 + 3 + x, a);
    ++y;
    a = M(W(0x06) + y);
    writeData(VRAM_Buffer2 + 4 + x, a);
    y = M(0x04);
    a = M(0x05);
    if (!z)
        goto RightCheck;
    a = M(0x01);
    a >>= 1;
    if (c)
        goto LLeft;
    M(0x03).rol();
    M(0x03).rol();
    M(0x03).rol();
    goto SetAttrib;
RightCheck:
    a = M(0x01);
    a >>= 1;
    if (c)
        goto NextMTRow;
    M(0x03) >>= 1;
    M(0x03) >>= 1;
    M(0x03) >>= 1;
    M(0x03) >>= 1;
    goto SetAttrib;
LLeft:
    M(0x03) >>= 1;
    M(0x03) >>= 1;
NextMTRow:
    ++M(0x04);
SetAttrib:
    a = M(AttributeBuffer + y);
    a |= M(0x03);
    writeData(AttributeBuffer + y, a);
    ++M(0x00);
    ++M(0x00);
    x = M(0x01);
    ++x;
    compare(x, 0x0d);
    if (!c)
        goto DrawMTLoop;
    y = M(0x00);
    ++y;
    ++y;
    ++y;
    a = 0x00;
    writeData(VRAM_Buffer2 + y, a);
    writeData(VRAM_Buffer2_Offset, y);
    ++M(CurrentNTAddr_Low);
    a = M(CurrentNTAddr_Low);
    a &= BOOST_BINARY(00011111);
    if (!z)
        goto ExitDrawM;
    a = 0x80;
    writeData(CurrentNTAddr_Low, a);
    a = M(CurrentNTAddr_High);
    a ^= BOOST_BINARY(00000100);
    writeData(CurrentNTAddr_High, a);
ExitDrawM:
    goto SetVRAMCtrl;
RenderAttributeTables:
    a = M(CurrentNTAddr_Low);
    a &= BOOST_BINARY(00011111);
    c = 1;
    a -= 0x04;
    a &= BOOST_BINARY(00011111);
    writeData(0x01, a);
    a = M(CurrentNTAddr_High);
    if (c)
        goto SetATHigh;
    a ^= BOOST_BINARY(00000100);
SetATHigh:
    a &= BOOST_BINARY(00000100);
    a |= 0x23;
    writeData(0x00, a);
    a = M(0x01);
    a >>= 1;
    a >>= 1;
    a += 0xc0;
    writeData(0x01, a);
    x = 0x00;
    y = M(VRAM_Buffer2_Offset);
AttribLoop:
    a = M(0x00);
    writeData(VRAM_Buffer2 + y, a);
    a = M(0x01);
    c = 0;
    a += 0x08;
    writeData(VRAM_Buffer2 + 1 + y, a);
    writeData(0x01, a);
    a = M(AttributeBuffer + x);
    writeData(VRAM_Buffer2 + 3 + y, a);
    a = 0x01;
    writeData(VRAM_Buffer2 + 2 + y, a);
    a >>= 1;
    writeData(AttributeBuffer + x, a);
    ++y;
    ++y;
    ++y;
    ++y;
    ++x;
    compare(x, 0x07);
    if (!c)
        goto AttribLoop;
    writeData(VRAM_Buffer2 + y, a);
    writeData(VRAM_Buffer2_Offset, y);
SetVRAMCtrl:
    a = 0x06;
    writeData(VRAM_Buffer_AddrCtrl, a);
    goto Return;

//---------------------------------------------------------------------

ColorRotation:
    a = M(FrameCounter);
    a &= 0x07;
    if (!z)
        goto ExitColorRot;
    x = M(VRAM_Buffer1_Offset);
    compare(x, 0x31);
    if (c)
        goto ExitColorRot;
    y = a;
GetBlankPal:
    a = M(BlankPalette + y);
    writeData(VRAM_Buffer1 + x, a);
    ++x;
    ++y;
    compare(y, 0x08);
    if (!c)
        goto GetBlankPal;
    x = M(VRAM_Buffer1_Offset);
    a = 0x03;
    writeData(0x00, a);
    a = M(AreaType);
    a <<= 1;
    a <<= 1;
    y = a;
GetAreaPal:
    a = M(Palette3Data + y);
    writeData(VRAM_Buffer1 + 3 + x, a);
    ++y;
    ++x;
    --M(0x00);
    if (!n)
        goto GetAreaPal;
    x = M(VRAM_Buffer1_Offset);
    y = M(ColorRotateOffset);
    a = M(ColorRotatePalette + y);
    writeData(VRAM_Buffer1 + 4 + x, a);
    a = M(VRAM_Buffer1_Offset);
    c = 0;
    a += 0x07;
    writeData(VRAM_Buffer1_Offset, a);
    ++M(ColorRotateOffset);
    a = M(ColorRotateOffset);
    compare(a, 0x06);
    if (!c)
        goto ExitColorRot;
    a = 0x00;
    writeData(ColorRotateOffset, a);
ExitColorRot:
    goto Return;

//---------------------------------------------------------------------

RemoveCoin_Axe:
    y = 0x41;
    a = 0x03;
    x = M(AreaType);
    if (!z)
        goto WriteBlankMT;
    a = 0x04;
WriteBlankMT:
    JSR(PutBlockMetatile, 42)
    a = 0x06;
    writeData(VRAM_Buffer_AddrCtrl, a);
    goto Return;

//---------------------------------------------------------------------

ReplaceBlockMetatile:
    JSR(WriteBlockMetatile, 43)
    ++M(Block_ResidualCounter);
    --M(Block_RepFlag + x);
    goto Return;

//---------------------------------------------------------------------

DestroyBlockMetatile:
    a = 0x00;
WriteBlockMetatile:
    y = 0x03;
    compare(a, 0x00);
    if (z)
        goto UseBOffset;
    y = 0x00;
    compare(a, 0x58);
    if (z)
        goto UseBOffset;
    compare(a, 0x51);
    if (z)
        goto UseBOffset;
    ++y;
    compare(a, 0x5d);
    if (z)
        goto UseBOffset;
    compare(a, 0x52);
    if (z)
        goto UseBOffset;
    ++y;
UseBOffset:
    a = y;
    y = M(VRAM_Buffer1_Offset);
    ++y;
    JSR(PutBlockMetatile, 44)
MoveVOffset:
    --y;
    a = y;
    c = 0;
    a += 10;
    goto SetVRAMOffset;
PutBlockMetatile:
    writeData(0x00, x);
    writeData(0x01, y);
    a <<= 1;
    a <<= 1;
    x = a;
    y = 0x20;
    a = M(0x06);
    compare(a, 0xd0);
    if (!c)
        goto SaveHAdder;
    y = 0x24;
SaveHAdder:
    writeData(0x03, y);
    a &= 0x0f;
    a <<= 1;
    writeData(0x04, a);
    a = 0x00;
    writeData(0x05, a);
    a = M(0x02);
    c = 0;
    a += 0x20;
    a <<= 1;
    M(0x05).rol();
    a <<= 1;
    M(0x05).rol();
    a += M(0x04);
    writeData(0x04, a);
    a = M(0x05);
    a += 0x00;
    c = 0;
    a += M(0x03);
    writeData(0x05, a);
    y = M(0x01);
RemBridge:
    a = M(BlockGfxData + x);
    writeData(VRAM_Buffer1 + 2 + y, a);
    a = M(BlockGfxData + 1 + x);
    writeData(VRAM_Buffer1 + 3 + y, a);
    a = M(BlockGfxData + 2 + x);
    writeData(VRAM_Buffer1 + 7 + y, a);
    a = M(BlockGfxData + 3 + x);
    writeData(VRAM_Buffer1 + 8 + y, a);
    a = M(0x04);
    writeData(VRAM_Buffer1 + y, a);
    c = 0;
    a += 0x20;
    writeData(VRAM_Buffer1 + 5 + y, a);
    a = M(0x05);
    writeData(VRAM_Buffer1 - 1 + y, a);
    writeData(VRAM_Buffer1 + 4 + y, a);
    a = 0x02;
    writeData(VRAM_Buffer1 + 1 + y, a);
    writeData(VRAM_Buffer1 + 6 + y, a);
    a = 0x00;
    writeData(VRAM_Buffer1 + 9 + y, a);
    x = M(0x00);
    goto Return;

//---------------------------------------------------------------------

InitializeNameTables:
    a = M(PPU_STATUS);
    a = M(Mirror_PPU_CTRL_REG1);
    a |= BOOST_BINARY(00010000);
    a &= BOOST_BINARY(11110000);
    JSR(WritePPUReg1, 45)
    a = 0x24;
    JSR(WriteNTAddr, 46)
    a = 0x20;
WriteNTAddr:
    writeData(PPU_ADDRESS, a);
    a = 0x00;
    writeData(PPU_ADDRESS, a);
    x = 0x04;
    y = 0xc0;
    a = 0x24;
InitNTLoop:
    writeData(PPU_DATA, a);
    --y;
    if (!z)
        goto InitNTLoop;
    --x;
    if (!z)
        goto InitNTLoop;
    y = 64;
    a = x;
    writeData(VRAM_Buffer1_Offset, a);
    writeData(VRAM_Buffer1, a);
InitATLoop:
    writeData(PPU_DATA, a);
    --y;
    if (!z)
        goto InitATLoop;
    writeData(HorizontalScroll, a);
    writeData(VerticalScroll, a);
    goto InitScroll;
ReadJoypads:
    a = 0x01;
    writeData(JOYPAD_PORT, a);
    a >>= 1;
    x = a;
    writeData(JOYPAD_PORT, a);
    JSR(ReadPortBits, 47)
    ++x;
ReadPortBits:
    y = 0x08;
PortLoop:
    pha();
    a = M(JOYPAD_PORT + x);
    writeData(0x00, a);
    a >>= 1;
    a |= M(0x00);
    a >>= 1;
    pla();
    a.rol();
    --y;
    if (!z)
        goto PortLoop;
    writeData(SavedJoypadBits + x, a);
    pha();
    a &= BOOST_BINARY(00110000);
    a &= M(JoypadBitMask + x);
    if (z)
        goto Save8Bits;
    pla();
    a &= BOOST_BINARY(11001111);
    writeData(SavedJoypadBits + x, a);
    goto Return;

//---------------------------------------------------------------------

Save8Bits:
    pla();
    writeData(JoypadBitMask + x, a);
    goto Return;

//---------------------------------------------------------------------

WriteBufferToScreen:
    writeData(PPU_ADDRESS, a);
    ++y;
    a = M(W(0x00) + y);
    writeData(PPU_ADDRESS, a);
    ++y;
    a = M(W(0x00) + y);
    a <<= 1;
    pha();
    a = M(Mirror_PPU_CTRL_REG1);
    a |= BOOST_BINARY(00000100);
    if (c)
        goto SetupWrites;
    a &= BOOST_BINARY(11111011);
SetupWrites:
    JSR(WritePPUReg1, 48)
    pla();
    a <<= 1;
    if (!c)
        goto GetLength;
    a |= BOOST_BINARY(00000010);
    ++y;
GetLength:
    a >>= 1;
    a >>= 1;
    x = a;
OutputToVRAM:
    if (c)
        goto RepeatByte;
    ++y;
RepeatByte:
    a = M(W(0x00) + y);
    writeData(PPU_DATA, a);
    --x;
    if (!z)
        goto OutputToVRAM;
    c = 1;
    a = y;
    a += M(0x00);
    writeData(0x00, a);
    a = 0x00;
    a += M(0x01);
    writeData(0x01, a);
    a = 0x3f;
    writeData(PPU_ADDRESS, a);
    a = 0x00;
    writeData(PPU_ADDRESS, a);
    writeData(PPU_ADDRESS, a);
    writeData(PPU_ADDRESS, a);
UpdateScreen:
    x = M(PPU_STATUS);
    y = 0x00;
    a = M(W(0x00) + y);
    if (!z)
        goto WriteBufferToScreen;
InitScroll:
    writeData(PPU_SCROLL_REG, a);
    writeData(PPU_SCROLL_REG, a);
    goto Return;

//---------------------------------------------------------------------

WritePPUReg1:
    writeData(PPU_CTRL_REG1, a);
    writeData(Mirror_PPU_CTRL_REG1, a);
    goto Return;

//---------------------------------------------------------------------

PrintStatusBarNumbers:
    writeData(0x00, a);
    JSR(OutputNumbers, 49)
    a = M(0x00);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
OutputNumbers:
    c = 0;
    a += 0x01;
    a &= BOOST_BINARY(00001111);
    compare(a, 0x06);
    if (c)
        goto ExitOutputN;
    pha();
    a <<= 1;
    y = a;
    x = M(VRAM_Buffer1_Offset);
    a = 0x20;
    compare(y, 0x00);
    if (!z)
        goto SetupNums;
    a = 0x22;
SetupNums:
    writeData(VRAM_Buffer1 + x, a);
    a = M(StatusBarData + y);
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = M(StatusBarData + 1 + y);
    writeData(VRAM_Buffer1 + 2 + x, a);
    writeData(0x03, a);
    writeData(0x02, x);
    pla();
    x = a;
    a = M(StatusBarOffset + x);
    c = 1;
    a -= M(StatusBarData + 1 + y);
    y = a;
    x = M(0x02);
DigitPLoop:
    a = M(DisplayDigits + y);
    writeData(VRAM_Buffer1 + 3 + x, a);
    ++x;
    ++y;
    --M(0x03);
    if (!z)
        goto DigitPLoop;
    a = 0x00;
    writeData(VRAM_Buffer1 + 3 + x, a);
    ++x;
    ++x;
    ++x;
    writeData(VRAM_Buffer1_Offset, x);
ExitOutputN:
    goto Return;

//---------------------------------------------------------------------

DigitsMathRoutine:
    a = M(OperMode);
    compare(a, TitleScreenModeValue);
    if (z)
        goto EraseDMods;
    x = 0x05;
AddModLoop:
    a = M(DigitModifier + x);
    c = 0;
    a += M(DisplayDigits + y);
    if (n)
        goto BorrowOne;
    compare(a, 10);
    if (c)
        goto CarryOne;
StoreNewD:
    writeData(DisplayDigits + y, a);
    --y;
    --x;
    if (!n)
        goto AddModLoop;
EraseDMods:
    a = 0x00;
    x = 0x06;
EraseMLoop:
    writeData(DigitModifier - 1 + x, a);
    --x;
    if (!n)
        goto EraseMLoop;
    goto Return;

//---------------------------------------------------------------------

BorrowOne:
    --M(DigitModifier - 1 + x);
    a = 0x09;
    if (!z)
        goto StoreNewD;
CarryOne:
    c = 1;
    a -= 10;
    ++M(DigitModifier - 1 + x);
    goto StoreNewD;
UpdateTopScore:
    x = 0x05;
    JSR(TopScoreCheck, 50)
    x = 0x0b;
TopScoreCheck:
    y = 0x05;
    c = 1;
GetScoreDiff:
    a = M(PlayerScoreDisplay + x);
    a -= M(TopScoreDisplay + y);
    --x;
    --y;
    if (!n)
        goto GetScoreDiff;
    if (!c)
        goto NoTopSc;
    ++x;
    ++y;
CopyScore:
    a = M(PlayerScoreDisplay + x);
    writeData(TopScoreDisplay + y, a);
    ++x;
    ++y;
    compare(y, 0x06);
    if (!c)
        goto CopyScore;
NoTopSc:
    goto Return;

//---------------------------------------------------------------------

InitializeGame:
    y = 0x6f;
    JSR(InitializeMemory, 51)
    y = 0x1f;
ClrSndLoop:
    writeData(SoundMemory + y, a);
    --y;
    if (!n)
        goto ClrSndLoop;
    a = 0x18;
    writeData(DemoTimer, a);
    JSR(LoadAreaPointer, 52)
InitializeArea:
    y = 0x4b;
    JSR(InitializeMemory, 53)
    x = 0x21;
    a = 0x00;
ClrTimersLoop:
    writeData(Timers + x, a);
    --x;
    if (!n)
        goto ClrTimersLoop;
    a = M(HalfwayPage);
    y = M(AltEntranceControl);
    if (z)
        goto StartPage;
    a = M(EntrancePage);
StartPage:
    writeData(ScreenLeft_PageLoc, a);
    writeData(CurrentPageLoc, a);
    writeData(BackloadingFlag, a);
    JSR(GetScreenPosition, 54)
    y = 0x20;
    a &= BOOST_BINARY(00000001);
    if (z)
        goto SetInitNTHigh;
    y = 0x24;
SetInitNTHigh:
    writeData(CurrentNTAddr_High, y);
    y = 0x80;
    writeData(CurrentNTAddr_Low, y);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    writeData(BlockBufferColumnPos, a);
    --M(AreaObjectLength);
    --M(AreaObjectLength + 1);
    --M(AreaObjectLength + 2);
    a = 0x0b;
    writeData(ColumnSets, a);
    JSR(GetAreaDataAddrs, 55)
    a = M(PrimaryHardMode);
    if (!z)
        goto SetSecHard;
    a = M(WorldNumber);
    compare(a, World5);
    if (!c)
        goto CheckHalfway;
    if (!z)
        goto SetSecHard;
    a = M(LevelNumber);
    compare(a, Level3);
    if (!c)
        goto CheckHalfway;
SetSecHard:
    ++M(SecondaryHardMode);
CheckHalfway:
    a = M(HalfwayPage);
    if (z)
        goto DoneInitArea;
    a = 0x02;
    writeData(PlayerEntranceCtrl, a);
DoneInitArea:
    a = Silence;
    writeData(AreaMusicQueue, a);
    a = 0x01;
    writeData(DisableScreenFlag, a);
    ++M(OperMode_Task);
    goto Return;

//---------------------------------------------------------------------

PrimaryGameSetup:
    a = 0x01;
    writeData(FetchNewGameTimerFlag, a);
    writeData(PlayerSize, a);
    a = 0x02;
    writeData(NumberofLives, a);
    writeData(OffScr_NumberofLives, a);
SecondaryGameSetup:
    a = 0x00;
    writeData(DisableScreenFlag, a);
    y = a;
ClearVRLoop:
    writeData(VRAM_Buffer1 - 1 + y, a);
    ++y;
    if (!z)
        goto ClearVRLoop;
    writeData(GameTimerExpiredFlag, a);
    writeData(DisableIntermediate, a);
    writeData(BackloadingFlag, a);
    a = 0xff;
    writeData(BalPlatformAlignment, a);
    a = M(ScreenLeft_PageLoc);
    M(Mirror_PPU_CTRL_REG1) >>= 1;
    a &= 0x01;
    a.ror();
    M(Mirror_PPU_CTRL_REG1).rol();
    JSR(GetAreaMusic, 56)
    a = 0x38;
    writeData(SprShuffleAmt + 2, a);
    a = 0x48;
    writeData(SprShuffleAmt + 1, a);
    a = 0x58;
    writeData(SprShuffleAmt, a);
    x = 0x0e;
ShufAmtLoop:
    a = M(DefaultSprOffsets + x);
    writeData(SprDataOffset + x, a);
    --x;
    if (!n)
        goto ShufAmtLoop;
    y = 0x03;
ISpr0Loop:
    a = M(Sprite0Data + y);
    writeData(Sprite_Data + y, a);
    --y;
    if (!n)
        goto ISpr0Loop;
    JSR(DoNothing2, 57)
    JSR(DoNothing1, 58)
    ++M(Sprite0HitDetectFlag);
    ++M(OperMode_Task);
    goto Return;

//---------------------------------------------------------------------

InitializeMemory:
    x = 0x07;
    a = 0x00;
    writeData(0x06, a);
InitPageLoop:
    writeData(0x07, x);
InitByteLoop:
    compare(x, 0x01);
    if (!z)
        goto InitByte;
    compare(y, 0x60);
    if (c)
        goto SkipByte;
InitByte:
    writeData(W(0x06) + y, a);
SkipByte:
    --y;
    compare(y, 0xff);
    if (!z)
        goto InitByteLoop;
    --x;
    if (!n)
        goto InitPageLoop;
    goto Return;

//---------------------------------------------------------------------

GetAreaMusic:
    a = M(OperMode);
    if (z)
        goto ExitGetM;
    a = M(AltEntranceControl);
    compare(a, 0x02);
    if (z)
        goto ChkAreaType;
    y = 0x05;
    a = M(PlayerEntranceCtrl);
    compare(a, 0x06);
    if (z)
        goto StoreMusic;
    compare(a, 0x07);
    if (z)
        goto StoreMusic;
ChkAreaType:
    y = M(AreaType);
    a = M(CloudTypeOverride);
    if (z)
        goto StoreMusic;
    y = 0x04;
StoreMusic:
    a = M(MusicSelectData + y);
    writeData(AreaMusicQueue, a);
ExitGetM:
    goto Return;

//---------------------------------------------------------------------

Entrance_GameTimerSetup:
    a = M(ScreenLeft_PageLoc);
    writeData(Player_PageLoc, a);
    a = 0x28;
    writeData(VerticalForceDown, a);
    a = 0x01;
    writeData(PlayerFacingDir, a);
    writeData(Player_Y_HighPos, a);
    a = 0x00;
    writeData(Player_State, a);
    --M(Player_CollisionBits);
    y = 0x00;
    writeData(HalfwayPage, y);
    a = M(AreaType);
    if (!z)
        goto ChkStPos;
    ++y;
ChkStPos:
    writeData(SwimmingFlag, y);
    x = M(PlayerEntranceCtrl);
    y = M(AltEntranceControl);
    if (z)
        goto SetStPos;
    compare(y, 0x01);
    if (z)
        goto SetStPos;
    x = M(AltYPosOffset - 2 + y);
SetStPos:
    a = M(PlayerStarting_X_Pos + y);
    writeData(Player_X_Position, a);
    a = M(PlayerStarting_Y_Pos + x);
    writeData(Player_Y_Position, a);
    a = M(PlayerBGPriorityData + x);
    writeData(Player_SprAttrib, a);
    JSR(GetPlayerColors, 59)
    y = M(GameTimerSetting);
    if (z)
        goto ChkOverR;
    a = M(FetchNewGameTimerFlag);
    if (z)
        goto ChkOverR;
    a = M(GameTimerData + y);
    writeData(GameTimerDisplay, a);
    a = 0x01;
    writeData(GameTimerDisplay + 2, a);
    a >>= 1;
    writeData(GameTimerDisplay + 1, a);
    writeData(FetchNewGameTimerFlag, a);
    writeData(StarInvincibleTimer, a);
ChkOverR:
    y = M(JoypadOverride);
    if (z)
        goto ChkSwimE;
    a = 0x03;
    writeData(Player_State, a);
    x = 0x00;
    JSR(InitBlock_XY_Pos, 60)
    a = 0xf0;
    writeData(Block_Y_Position, a);
    x = 0x05;
    y = 0x00;
    JSR(Setup_Vine, 61)
ChkSwimE:
    y = M(AreaType);
    if (!z)
        goto SetPESub;
    JSR(SetupBubble, 62)
SetPESub:
    a = 0x07;
    writeData(GameEngineSubroutine, a);
    goto Return;

//---------------------------------------------------------------------

PlayerLoseLife:
    ++M(DisableScreenFlag);
    a = 0x00;
    writeData(Sprite0HitDetectFlag, a);
    a = Silence;
    writeData(EventMusicQueue, a);
    --M(NumberofLives);
    if (!n)
        goto StillInGame;
    a = 0x00;
    writeData(OperMode_Task, a);
    a = GameOverModeValue;
    writeData(OperMode, a);
    goto Return;

//---------------------------------------------------------------------

StillInGame:
    a = M(WorldNumber);
    a <<= 1;
    x = a;
    a = M(LevelNumber);
    a &= 0x02;
    if (z)
        goto GetHalfway;
    ++x;
GetHalfway:
    y = M(HalfwayPageNybbles + x);
    a = M(LevelNumber);
    a >>= 1;
    a = y;
    if (c)
        goto MaskHPNyb;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
MaskHPNyb:
    a &= BOOST_BINARY(00001111);
    compare(a, M(ScreenLeft_PageLoc));
    if (z)
        goto SetHalfway;
    if (!c)
        goto SetHalfway;
    a = 0x00;
SetHalfway:
    writeData(HalfwayPage, a);
    JSR(TransposePlayers, 63)
    goto ContinueGame;
GameOverMode:
    a = M(OperMode_Task);
    switch(a)
        {
    case 0:
        goto SetupGameOver;
    case 1:
        goto ScreenRoutines;
    case 2:
        goto RunGameOver;
    }
SetupGameOver:
    a = 0x00;
    writeData(ScreenRoutineTask, a);
    writeData(Sprite0HitDetectFlag, a);
    a = GameOverMusic;
    writeData(EventMusicQueue, a);
    ++M(DisableScreenFlag);
    ++M(OperMode_Task);
    goto Return;

//---------------------------------------------------------------------

RunGameOver:
    a = 0x00;
    writeData(DisableScreenFlag, a);
    a = M(SavedJoypad1Bits);
    a &= Start_Button;
    if (!z)
        goto TerminateGame;
    a = M(ScreenTimer);
    if (!z)
        goto GameIsOn;
TerminateGame:
    a = Silence;
    writeData(EventMusicQueue, a);
    JSR(TransposePlayers, 64)
    if (!c)
        goto ContinueGame;
    a = M(WorldNumber);
    writeData(ContinueWorld, a);
    a = 0x00;
    a <<= 1;
    writeData(OperMode_Task, a);
    writeData(ScreenTimer, a);
    writeData(OperMode, a);
    goto Return;

//---------------------------------------------------------------------

ContinueGame:
    JSR(LoadAreaPointer, 65)
    a = 0x01;
    writeData(PlayerSize, a);
    ++M(FetchNewGameTimerFlag);
    a = 0x00;
    writeData(TimerControl, a);
    writeData(PlayerStatus, a);
    writeData(GameEngineSubroutine, a);
    writeData(OperMode_Task, a);
    a = 0x01;
    writeData(OperMode, a);
GameIsOn:
    goto Return;

//---------------------------------------------------------------------

TransposePlayers:
    c = 1;
    a = M(NumberOfPlayers);
    if (z)
        goto ExTrans;
    a = M(OffScr_NumberofLives);
    if (n)
        goto ExTrans;
    a = M(CurrentPlayer);
    a ^= BOOST_BINARY(00000001);
    writeData(CurrentPlayer, a);
    x = 0x06;
TransLoop:
    a = M(OnscreenPlayerInfo + x);
    pha();
    a = M(OffscreenPlayerInfo + x);
    writeData(OnscreenPlayerInfo + x, a);
    pla();
    writeData(OffscreenPlayerInfo + x, a);
    --x;
    if (!n)
        goto TransLoop;
    c = 0;
ExTrans:
    goto Return;

//---------------------------------------------------------------------

DoNothing1:
    a = 0xff;
    writeData(0x06c9, a);
DoNothing2:
    goto Return;

//---------------------------------------------------------------------

AreaParserTaskHandler:
    y = M(AreaParserTaskNum);
    if (!z)
        goto DoAPTasks;
    y = 0x08;
    writeData(AreaParserTaskNum, y);
DoAPTasks:
    --y;
    a = y;
    JSR(AreaParserTasks, 66)
    --M(AreaParserTaskNum);
    if (!z)
        goto SkipATRender;
    JSR(RenderAttributeTables, 67)
SkipATRender:
    goto Return;

//---------------------------------------------------------------------

AreaParserTasks:
    switch(a)
        {
    case 0:
        goto IncrementColumnPos;
    case 1:
        goto RenderAreaGraphics;
    case 2:
        goto RenderAreaGraphics;
    case 3:
        goto AreaParserCore;
    case 4:
        goto IncrementColumnPos;
    case 5:
        goto RenderAreaGraphics;
    case 6:
        goto RenderAreaGraphics;
    case 7:
        goto AreaParserCore;
    }
IncrementColumnPos:
    ++M(CurrentColumnPos);
    a = M(CurrentColumnPos);
    a &= BOOST_BINARY(00001111);
    if (!z)
        goto NoColWrap;
    writeData(CurrentColumnPos, a);
    ++M(CurrentPageLoc);
NoColWrap:
    ++M(BlockBufferColumnPos);
    a = M(BlockBufferColumnPos);
    a &= BOOST_BINARY(00011111);
    writeData(BlockBufferColumnPos, a);
    goto Return;

//---------------------------------------------------------------------

AreaParserCore:
    a = M(BackloadingFlag);
    if (z)
        goto RenderSceneryTerrain;
    JSR(ProcessAreaData, 68)
RenderSceneryTerrain:
    x = 0x0c;
    a = 0x00;
ClrMTBuf:
    writeData(MetatileBuffer + x, a);
    --x;
    if (!n)
        goto ClrMTBuf;
    y = M(BackgroundScenery);
    if (z)
        goto RendFore;
    a = M(CurrentPageLoc);
ThirdP:
    compare(a, 0x03);
    if (n)
        goto RendBack;
    c = 1;
    a -= 0x03;
    if (!n)
        goto ThirdP;
RendBack:
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a += M(BSceneDataOffsets - 1 + y);
    a += M(CurrentColumnPos);
    x = a;
    a = M(BackSceneryData + x);
    if (z)
        goto RendFore;
    pha();
    a &= 0x0f;
    c = 1;
    a -= 0x01;
    writeData(0x00, a);
    a <<= 1;
    a += M(0x00);
    x = a;
    pla();
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    y = a;
    a = 0x03;
    writeData(0x00, a);
SceLoop1:
    a = M(BackSceneryMetatiles + x);
    writeData(MetatileBuffer + y, a);
    ++x;
    ++y;
    compare(y, 0x0b);
    if (z)
        goto RendFore;
    --M(0x00);
    if (!z)
        goto SceLoop1;
RendFore:
    x = M(ForegroundScenery);
    if (z)
        goto RendTerr;
    y = M(FSceneDataOffsets - 1 + x);
    x = 0x00;
SceLoop2:
    a = M(ForeSceneryData + y);
    if (z)
        goto NoFore;
    writeData(MetatileBuffer + x, a);
NoFore:
    ++y;
    ++x;
    compare(x, 0x0d);
    if (!z)
        goto SceLoop2;
RendTerr:
    y = M(AreaType);
    if (!z)
        goto TerMTile;
    a = M(WorldNumber);
    compare(a, World8);
    if (!z)
        goto TerMTile;
    a = 0x62;
    goto StoreMT;
TerMTile:
    a = M(TerrainMetatiles + y);
    y = M(CloudTypeOverride);
    if (z)
        goto StoreMT;
    a = 0x88;
StoreMT:
    writeData(0x07, a);
    x = 0x00;
    a = M(TerrainControl);
    a <<= 1;
    y = a;
TerrLoop:
    a = M(TerrainRenderBits + y);
    writeData(0x00, a);
    ++y;
    writeData(0x01, y);
    a = M(CloudTypeOverride);
    if (z)
        goto NoCloud2;
    compare(x, 0x00);
    if (z)
        goto NoCloud2;
    a = M(0x00);
    a &= BOOST_BINARY(00001000);
    writeData(0x00, a);
NoCloud2:
    y = 0x00;
TerrBChk:
    a = M(Bitmasks + y);
    bit(M(0x00));
    if (z)
        goto NextTBit;
    a = M(0x07);
    writeData(MetatileBuffer + x, a);
NextTBit:
    ++x;
    compare(x, 0x0d);
    if (z)
        goto RendBBuf;
    a = M(AreaType);
    compare(a, 0x02);
    if (!z)
        goto EndUChk;
    compare(x, 0x0b);
    if (!z)
        goto EndUChk;
    a = 0x54;
    writeData(0x07, a);
EndUChk:
    ++y;
    compare(y, 0x08);
    if (!z)
        goto TerrBChk;
    y = M(0x01);
    if (!z)
        goto TerrLoop;
RendBBuf:
    JSR(ProcessAreaData, 69)
    a = M(BlockBufferColumnPos);
    JSR(GetBlockBufferAddr, 70)
    x = 0x00;
    y = 0x00;
ChkMTLow:
    writeData(0x00, y);
    a = M(MetatileBuffer + x);
    a &= BOOST_BINARY(11000000);
    a <<= 1;
    a.rol();
    a.rol();
    y = a;
    a = M(MetatileBuffer + x);
    compare(a, M(BlockBuffLowBounds + y));
    if (c)
        goto StrBlock;
    a = 0x00;
StrBlock:
    y = M(0x00);
    writeData(W(0x06) + y, a);
    a = y;
    c = 0;
    a += 0x10;
    y = a;
    ++x;
    compare(x, 0x0d);
    if (!c)
        goto ChkMTLow;
    goto Return;

//---------------------------------------------------------------------

ProcessAreaData:
    x = 0x02;
ProcADLoop:
    writeData(ObjectOffset, x);
    a = 0x00;
    writeData(BehindAreaParserFlag, a);
    y = M(AreaDataOffset);
    a = M(W(AreaData) + y);
    compare(a, 0xfd);
    if (z)
        goto RdyDecode;
    a = M(AreaObjectLength + x);
    if (!n)
        goto RdyDecode;
    ++y;
    a = M(W(AreaData) + y);
    a <<= 1;
    if (!c)
        goto Chk1Row13;
    a = M(AreaObjectPageSel);
    if (!z)
        goto Chk1Row13;
    ++M(AreaObjectPageSel);
    ++M(AreaObjectPageLoc);
Chk1Row13:
    --y;
    a = M(W(AreaData) + y);
    a &= 0x0f;
    compare(a, 0x0d);
    if (!z)
        goto Chk1Row14;
    ++y;
    a = M(W(AreaData) + y);
    --y;
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto CheckRear;
    a = M(AreaObjectPageSel);
    if (!z)
        goto CheckRear;
    ++y;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00011111);
    writeData(AreaObjectPageLoc, a);
    ++M(AreaObjectPageSel);
    goto NextAObj;
Chk1Row14:
    compare(a, 0x0e);
    if (!z)
        goto CheckRear;
    a = M(BackloadingFlag);
    if (!z)
        goto RdyDecode;
CheckRear:
    a = M(AreaObjectPageLoc);
    compare(a, M(CurrentPageLoc));
    if (!c)
        goto SetBehind;
RdyDecode:
    JSR(DecodeAreaData, 71)
    goto ChkLength;
SetBehind:
    ++M(BehindAreaParserFlag);
NextAObj:
    JSR(IncAreaObjOffset, 72)
ChkLength:
    x = M(ObjectOffset);
    a = M(AreaObjectLength + x);
    if (n)
        goto ProcLoopb;
    --M(AreaObjectLength + x);
ProcLoopb:
    --x;
    if (!n)
        goto ProcADLoop;
    a = M(BehindAreaParserFlag);
    if (!z)
        goto ProcessAreaData;
    a = M(BackloadingFlag);
    if (!z)
        goto ProcessAreaData;
EndAParse:
    goto Return;

//---------------------------------------------------------------------

IncAreaObjOffset:
    ++M(AreaDataOffset);
    ++M(AreaDataOffset);
    a = 0x00;
    writeData(AreaObjectPageSel, a);
    goto Return;

//---------------------------------------------------------------------

DecodeAreaData:
    a = M(AreaObjectLength + x);
    if (n)
        goto Chk1stB;
    y = M(AreaObjOffsetBuffer + x);
Chk1stB:
    x = 0x10;
    a = M(W(AreaData) + y);
    compare(a, 0xfd);
    if (z)
        goto EndAParse;
    a &= 0x0f;
    compare(a, 0x0f);
    if (z)
        goto ChkRow14;
    x = 0x08;
    compare(a, 0x0c);
    if (z)
        goto ChkRow14;
    x = 0x00;
ChkRow14:
    writeData(0x07, x);
    x = M(ObjectOffset);
    compare(a, 0x0e);
    if (!z)
        goto ChkRow13;
    a = 0x00;
    writeData(0x07, a);
    a = 0x2e;
    if (!z)
        goto NormObj;
ChkRow13:
    compare(a, 0x0d);
    if (!z)
        goto ChkSRows;
    a = 0x22;
    writeData(0x07, a);
    ++y;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(01000000);
    if (z)
        goto LeavePar;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(01111111);
    compare(a, 0x4b);
    if (!z)
        goto Mask2MSB;
    ++M(LoopCommand);
Mask2MSB:
    a &= BOOST_BINARY(00111111);
    goto NormObj;
ChkSRows:
    compare(a, 0x0c);
    if (c)
        goto SpecObj;
    ++y;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(01110000);
    if (!z)
        goto LrgObj;
    a = 0x16;
    writeData(0x07, a);
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00001111);
    goto NormObj;
LrgObj:
    writeData(0x00, a);
    compare(a, 0x70);
    if (!z)
        goto NotWPipe;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00001000);
    if (z)
        goto NotWPipe;
    a = 0x00;
    writeData(0x00, a);
NotWPipe:
    a = M(0x00);
    goto MoveAOId;
SpecObj:
    ++y;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(01110000);
MoveAOId:
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
NormObj:
    writeData(0x00, a);
    a = M(AreaObjectLength + x);
    if (!n)
        goto RunAObj;
    a = M(AreaObjectPageLoc);
    compare(a, M(CurrentPageLoc));
    if (z)
        goto InitRear;
    y = M(AreaDataOffset);
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00001111);
    compare(a, 0x0e);
    if (!z)
        goto LeavePar;
    a = M(BackloadingFlag);
    if (!z)
        goto StrAObj;
LeavePar:
    goto Return;

//---------------------------------------------------------------------

InitRear:
    a = M(BackloadingFlag);
    if (z)
        goto BackColC;
    a = 0x00;
    writeData(BackloadingFlag, a);
    writeData(BehindAreaParserFlag, a);
    writeData(ObjectOffset, a);
LoopCmdE:
    goto Return;

//---------------------------------------------------------------------

BackColC:
    y = M(AreaDataOffset);
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(11110000);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    compare(a, M(CurrentColumnPos));
    if (!z)
        goto LeavePar;
StrAObj:
    a = M(AreaDataOffset);
    writeData(AreaObjOffsetBuffer + x, a);
    JSR(IncAreaObjOffset, 73)
RunAObj:
    a = M(0x00);
    c = 0;
    a += M(0x07);
    switch(a)
        {
    case 0:
        goto VerticalPipe;
    case 1:
        goto AreaStyleObject;
    case 2:
        goto RowOfBricks;
    case 3:
        goto RowOfSolidBlocks;
    case 4:
        goto RowOfCoins;
    case 5:
        goto ColumnOfBricks;
    case 6:
        goto ColumnOfSolidBlocks;
    case 7:
        goto VerticalPipe;
    case 8:
        goto Hole_Empty;
    case 9:
        goto PulleyRopeObject;
    case 10:
        goto Bridge_High;
    case 11:
        goto Bridge_Middle;
    case 12:
        goto Bridge_Low;
    case 13:
        goto Hole_Water;
    case 14:
        goto QuestionBlockRow_High;
    case 15:
        goto QuestionBlockRow_Low;
    case 16:
        goto EndlessRope;
    case 17:
        goto BalancePlatRope;
    case 18:
        goto CastleObject;
    case 19:
        goto StaircaseObject;
    case 20:
        goto ExitPipe;
    case 21:
        goto FlagBalls_Residual;
    case 22:
        goto QuestionBlock;
    case 23:
        goto QuestionBlock;
    case 24:
        goto QuestionBlock;
    case 25:
        goto Hidden1UpBlock;
    case 26:
        goto BrickWithItem;
    case 27:
        goto BrickWithItem;
    case 28:
        goto BrickWithItem;
    case 29:
        goto BrickWithCoins;
    case 30:
        goto BrickWithItem;
    case 31:
        goto WaterPipe;
    case 32:
        goto EmptyBlock;
    case 33:
        goto Jumpspring;
    case 34:
        goto IntroPipe;
    case 35:
        goto FlagpoleObject;
    case 36:
        goto AxeObj;
    case 37:
        goto ChainObj;
    case 38:
        goto CastleBridgeObj;
    case 39:
        goto ScrollLockObject_Warp;
    case 40:
        goto ScrollLockObject;
    case 41:
        goto ScrollLockObject;
    case 42:
        goto AreaFrenzy;
    case 43:
        goto AreaFrenzy;
    case 44:
        goto AreaFrenzy;
    case 45:
        goto LoopCmdE;
    case 46:
        goto AlterAreaAttributes;
    }
AlterAreaAttributes:
    y = M(AreaObjOffsetBuffer + x);
    ++y;
    a = M(W(AreaData) + y);
    pha();
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto Alter2;
    pla();
    pha();
    a &= BOOST_BINARY(00001111);
    writeData(TerrainControl, a);
    pla();
    a &= BOOST_BINARY(00110000);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(BackgroundScenery, a);
    goto Return;

//---------------------------------------------------------------------

Alter2:
    pla();
    a &= BOOST_BINARY(00000111);
    compare(a, 0x04);
    if (!c)
        goto SetFore;
    writeData(BackgroundColorCtrl, a);
    a = 0x00;
SetFore:
    writeData(ForegroundScenery, a);
    goto Return;

//---------------------------------------------------------------------

ScrollLockObject_Warp:
    x = 0x04;
    a = M(WorldNumber);
    if (z)
        goto WarpNum;
    ++x;
    y = M(AreaType);
    --y;
    if (!z)
        goto WarpNum;
    ++x;
WarpNum:
    a = x;
    writeData(WarpZoneControl, a);
    JSR(WriteGameText, 74)
    a = PiranhaPlant;
    JSR(KillEnemies, 75)
ScrollLockObject:
    a = M(ScrollLock);
    a ^= BOOST_BINARY(00000001);
    writeData(ScrollLock, a);
    goto Return;

//---------------------------------------------------------------------

KillEnemies:
    writeData(0x00, a);
    a = 0x00;
    x = 0x04;
KillELoop:
    y = M(Enemy_ID + x);
    compare(y, M(0x00));
    if (!z)
        goto NoKillE;
    writeData(Enemy_Flag + x, a);
NoKillE:
    --x;
    if (!n)
        goto KillELoop;
    goto Return;

//---------------------------------------------------------------------

AreaFrenzy:
    x = M(0x00);
    a = M(FrenzyIDData - 8 + x);
    y = 0x05;
FreCompLoop:
    --y;
    if (n)
        goto ExitAFrenzy;
    compare(a, M(Enemy_ID + y));
    if (!z)
        goto FreCompLoop;
    a = 0x00;
ExitAFrenzy:
    writeData(EnemyFrenzyQueue, a);
    goto Return;

//---------------------------------------------------------------------

AreaStyleObject:
    a = M(AreaStyle);
    switch(a)
        {
    case 0:
        goto TreeLedge;
    case 1:
        goto MushroomLedge;
    case 2:
        goto BulletBillCannon;
    }
TreeLedge:
    JSR(GetLrgObjAttrib, 76)
    a = M(AreaObjectLength + x);
    if (z)
        goto EndTreeL;
    if (!n)
        goto MidTreeL;
    a = y;
    writeData(AreaObjectLength + x, a);
    a = M(CurrentPageLoc);
    a |= M(CurrentColumnPos);
    if (z)
        goto MidTreeL;
    a = 0x16;
    goto NoUnder;
MidTreeL:
    x = M(0x07);
    a = 0x17;
    writeData(MetatileBuffer + x, a);
    a = 0x4c;
    goto AllUnder;
EndTreeL:
    a = 0x18;
    goto NoUnder;
MushroomLedge:
    JSR(ChkLrgObjLength, 77)
    writeData(0x06, y);
    if (!c)
        goto EndMushL;
    a = M(AreaObjectLength + x);
    a >>= 1;
    writeData(MushroomLedgeHalfLen + x, a);
    a = 0x19;
    goto NoUnder;
EndMushL:
    a = 0x1b;
    y = M(AreaObjectLength + x);
    if (z)
        goto NoUnder;
    a = M(MushroomLedgeHalfLen + x);
    writeData(0x06, a);
    x = M(0x07);
    a = 0x1a;
    writeData(MetatileBuffer + x, a);
    compare(y, M(0x06));
    if (!z)
        goto MushLExit;
    ++x;
    a = 0x4f;
    writeData(MetatileBuffer + x, a);
    a = 0x50;
AllUnder:
    ++x;
    y = 0x0f;
    goto RenderUnderPart;
NoUnder:
    x = M(0x07);
    y = 0x00;
    goto RenderUnderPart;
PulleyRopeObject:
    JSR(ChkLrgObjLength, 78)
    y = 0x00;
    if (c)
        goto RenderPul;
    ++y;
    a = M(AreaObjectLength + x);
    if (!z)
        goto RenderPul;
    ++y;
RenderPul:
    a = M(PulleyRopeMetatiles + y);
    writeData(MetatileBuffer, a);
MushLExit:
    goto Return;

//---------------------------------------------------------------------

CastleObject:
    JSR(GetLrgObjAttrib, 79)
    writeData(0x07, y);
    y = 0x04;
    JSR(ChkLrgObjFixedLength, 80)
    a = x;
    pha();
    y = M(AreaObjectLength + x);
    x = M(0x07);
    a = 0x0b;
    writeData(0x06, a);
CRendLoop:
    a = M(CastleMetatiles + y);
    writeData(MetatileBuffer + x, a);
    ++x;
    a = M(0x06);
    if (z)
        goto ChkCFloor;
    ++y;
    ++y;
    ++y;
    ++y;
    ++y;
    --M(0x06);
ChkCFloor:
    compare(x, 0x0b);
    if (!z)
        goto CRendLoop;
    pla();
    x = a;
    a = M(CurrentPageLoc);
    if (z)
        goto ExitCastle;
    a = M(AreaObjectLength + x);
    compare(a, 0x01);
    if (z)
        goto PlayerStop;
    y = M(0x07);
    if (!z)
        goto NotTall;
    compare(a, 0x03);
    if (z)
        goto PlayerStop;
NotTall:
    compare(a, 0x02);
    if (!z)
        goto ExitCastle;
    JSR(GetAreaObjXPosition, 81)
    pha();
    JSR(FindEmptyEnemySlot, 82)
    pla();
    writeData(Enemy_X_Position + x, a);
    a = M(CurrentPageLoc);
    writeData(Enemy_PageLoc + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    a = 0x90;
    writeData(Enemy_Y_Position + x, a);
    a = StarFlagObject;
    writeData(Enemy_ID + x, a);
    goto Return;

//---------------------------------------------------------------------

PlayerStop:
    y = 0x52;
    writeData(MetatileBuffer + 10, y);
ExitCastle:
    goto Return;

//---------------------------------------------------------------------

WaterPipe:
    JSR(GetLrgObjAttrib, 83)
    y = M(AreaObjectLength + x);
    x = M(0x07);
    a = 0x6b;
    writeData(MetatileBuffer + x, a);
    a = 0x6c;
    writeData(MetatileBuffer + 1 + x, a);
    goto Return;

//---------------------------------------------------------------------

IntroPipe:
    y = 0x03;
    JSR(ChkLrgObjFixedLength, 84)
    y = 0x0a;
    JSR(RenderSidewaysPipe, 85)
    if (c)
        goto NoBlankP;
    x = 0x06;
VPipeSectLoop:
    a = 0x00;
    writeData(MetatileBuffer + x, a);
    --x;
    if (!n)
        goto VPipeSectLoop;
    a = M(VerticalPipeData + y);
    writeData(MetatileBuffer + 7, a);
NoBlankP:
    goto Return;

//---------------------------------------------------------------------

ExitPipe:
    y = 0x03;
    JSR(ChkLrgObjFixedLength, 86)
    JSR(GetLrgObjAttrib, 87)
RenderSidewaysPipe:
    --y;
    --y;
    writeData(0x05, y);
    y = M(AreaObjectLength + x);
    writeData(0x06, y);
    x = M(0x05);
    ++x;
    a = M(SidePipeShaftData + y);
    compare(a, 0x00);
    if (z)
        goto DrawSidePart;
    x = 0x00;
    y = M(0x05);
    JSR(RenderUnderPart, 88)
    c = 0;
DrawSidePart:
    y = M(0x06);
    a = M(SidePipeTopPart + y);
    writeData(MetatileBuffer + x, a);
    a = M(SidePipeBottomPart + y);
    writeData(MetatileBuffer + 1 + x, a);
    goto Return;

//---------------------------------------------------------------------

VerticalPipe:
    JSR(GetPipeHeight, 89)
    a = M(0x00);
    if (z)
        goto WarpPipe;
    ++y;
    ++y;
    ++y;
    ++y;
WarpPipe:
    a = y;
    pha();
    a = M(AreaNumber);
    a |= M(WorldNumber);
    if (z)
        goto DrawPipe;
    y = M(AreaObjectLength + x);
    if (z)
        goto DrawPipe;
    JSR(FindEmptyEnemySlot, 90)
    if (c)
        goto DrawPipe;
    JSR(GetAreaObjXPosition, 91)
    c = 0;
    a += 0x08;
    writeData(Enemy_X_Position + x, a);
    a = M(CurrentPageLoc);
    a += 0x00;
    writeData(Enemy_PageLoc + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    JSR(GetAreaObjYPosition, 92)
    writeData(Enemy_Y_Position + x, a);
    a = PiranhaPlant;
    writeData(Enemy_ID + x, a);
    JSR(InitPiranhaPlant, 93)
DrawPipe:
    pla();
    y = a;
    x = M(0x07);
    a = M(VerticalPipeData + y);
    writeData(MetatileBuffer + x, a);
    ++x;
    a = M(VerticalPipeData + 2 + y);
    y = M(0x06);
    --y;
    goto RenderUnderPart;
GetPipeHeight:
    y = 0x01;
    JSR(ChkLrgObjFixedLength, 94)
    JSR(GetLrgObjAttrib, 95)
    a = y;
    a &= 0x07;
    writeData(0x06, a);
    y = M(AreaObjectLength + x);
    goto Return;

//---------------------------------------------------------------------

FindEmptyEnemySlot:
    x = 0x00;
EmptyChkLoop:
    c = 0;
    a = M(Enemy_Flag + x);
    if (z)
        goto ExitEmptyChk;
    ++x;
    compare(x, 0x05);
    if (!z)
        goto EmptyChkLoop;
ExitEmptyChk:
    goto Return;

//---------------------------------------------------------------------

Hole_Water:
    JSR(ChkLrgObjLength, 96)
    a = 0x86;
    writeData(MetatileBuffer + 10, a);
    x = 0x0b;
    y = 0x01;
    a = 0x87;
    goto RenderUnderPart;
QuestionBlockRow_High:
    a = 0x03;
    goto Skip_1;
QuestionBlockRow_Low:
    a = 0x07;
Skip_1:
    pha();
    JSR(ChkLrgObjLength, 97)
    pla();
    x = a;
    a = 0xc0;
    writeData(MetatileBuffer + x, a);
    goto Return;

//---------------------------------------------------------------------

Bridge_High:
    a = 0x06;
    goto Skip_2;
Bridge_Middle:
    a = 0x07;
Skip_2:
    goto Skip_3;
Bridge_Low:
    a = 0x09;
Skip_3:
    pha();
    JSR(ChkLrgObjLength, 98)
    pla();
    x = a;
    a = 0x0b;
    writeData(MetatileBuffer + x, a);
    ++x;
    y = 0x00;
    a = 0x63;
    goto RenderUnderPart;
FlagBalls_Residual:
    JSR(GetLrgObjAttrib, 99)
    x = 0x02;
    a = 0x6d;
    goto RenderUnderPart;
FlagpoleObject:
    a = 0x24;
    writeData(MetatileBuffer, a);
    x = 0x01;
    y = 0x08;
    a = 0x25;
    JSR(RenderUnderPart, 100)
    a = 0x61;
    writeData(MetatileBuffer + 10, a);
    JSR(GetAreaObjXPosition, 101)
    c = 1;
    a -= 0x08;
    writeData(Enemy_X_Position + 5, a);
    a = M(CurrentPageLoc);
    a -= 0x00;
    writeData(Enemy_PageLoc + 5, a);
    a = 0x30;
    writeData(Enemy_Y_Position + 5, a);
    a = 0xb0;
    writeData(FlagpoleFNum_Y_Pos, a);
    a = FlagpoleFlagObject;
    writeData(Enemy_ID + 5, a);
    ++M(Enemy_Flag + 5);
    goto Return;

//---------------------------------------------------------------------

EndlessRope:
    x = 0x00;
    y = 0x0f;
    goto DrawRope;
BalancePlatRope:
    a = x;
    pha();
    x = 0x01;
    y = 0x0f;
    a = 0x44;
    JSR(RenderUnderPart, 102)
    pla();
    x = a;
    JSR(GetLrgObjAttrib, 103)
    x = 0x01;
DrawRope:
    a = 0x40;
    goto RenderUnderPart;
RowOfCoins:
    y = M(AreaType);
    a = M(CoinMetatileData + y);
    goto GetRow;
CastleBridgeObj:
    y = 0x0c;
    JSR(ChkLrgObjFixedLength, 104)
    goto ChainObj;
AxeObj:
    a = 0x08;
    writeData(VRAM_Buffer_AddrCtrl, a);
ChainObj:
    y = M(0x00);
    x = M(C_ObjectRow - 2 + y);
    a = M(C_ObjectMetatile - 2 + y);
    goto ColObj;
EmptyBlock:
    JSR(GetLrgObjAttrib, 105)
    x = M(0x07);
    a = 0xc4;
ColObj:
    y = 0x00;
    goto RenderUnderPart;
RowOfBricks:
    y = M(AreaType);
    a = M(CloudTypeOverride);
    if (z)
        goto DrawBricks;
    y = 0x04;
DrawBricks:
    a = M(BrickMetatiles + y);
    goto GetRow;
RowOfSolidBlocks:
    y = M(AreaType);
    a = M(SolidBlockMetatiles + y);
GetRow:
    pha();
    JSR(ChkLrgObjLength, 106)
DrawRow:
    x = M(0x07);
    y = 0x00;
    pla();
    goto RenderUnderPart;
ColumnOfBricks:
    y = M(AreaType);
    a = M(BrickMetatiles + y);
    goto GetRow2;
ColumnOfSolidBlocks:
    y = M(AreaType);
    a = M(SolidBlockMetatiles + y);
GetRow2:
    pha();
    JSR(GetLrgObjAttrib, 107)
    pla();
    x = M(0x07);
    goto RenderUnderPart;
BulletBillCannon:
    JSR(GetLrgObjAttrib, 108)
    x = M(0x07);
    a = 0x64;
    writeData(MetatileBuffer + x, a);
    ++x;
    --y;
    if (n)
        goto SetupCannon;
    a = 0x65;
    writeData(MetatileBuffer + x, a);
    ++x;
    --y;
    if (n)
        goto SetupCannon;
    a = 0x66;
    JSR(RenderUnderPart, 109)
SetupCannon:
    x = M(Cannon_Offset);
    JSR(GetAreaObjYPosition, 110)
    writeData(Cannon_Y_Position + x, a);
    a = M(CurrentPageLoc);
    writeData(Cannon_PageLoc + x, a);
    JSR(GetAreaObjXPosition, 111)
    writeData(Cannon_X_Position + x, a);
    ++x;
    compare(x, 0x06);
    if (!c)
        goto StrCOffset;
    x = 0x00;
StrCOffset:
    writeData(Cannon_Offset, x);
    goto Return;

//---------------------------------------------------------------------

StaircaseObject:
    JSR(ChkLrgObjLength, 112)
    if (!c)
        goto NextStair;
    a = 0x09;
    writeData(StaircaseControl, a);
NextStair:
    --M(StaircaseControl);
    y = M(StaircaseControl);
    x = M(StaircaseRowData + y);
    a = M(StaircaseHeightData + y);
    y = a;
    a = 0x61;
    goto RenderUnderPart;
Jumpspring:
    JSR(GetLrgObjAttrib, 113)
    JSR(FindEmptyEnemySlot, 114)
    JSR(GetAreaObjXPosition, 115)
    writeData(Enemy_X_Position + x, a);
    a = M(CurrentPageLoc);
    writeData(Enemy_PageLoc + x, a);
    JSR(GetAreaObjYPosition, 116)
    writeData(Enemy_Y_Position + x, a);
    writeData(Jumpspring_FixedYPos + x, a);
    a = JumpspringObject;
    writeData(Enemy_ID + x, a);
    y = 0x01;
    writeData(Enemy_Y_HighPos + x, y);
    ++M(Enemy_Flag + x);
    x = M(0x07);
    a = 0x67;
    writeData(MetatileBuffer + x, a);
    a = 0x68;
    writeData(MetatileBuffer + 1 + x, a);
    goto Return;

//---------------------------------------------------------------------

Hidden1UpBlock:
    a = M(Hidden1UpFlag);
    if (z)
        goto ExitDecBlock;
    a = 0x00;
    writeData(Hidden1UpFlag, a);
    goto BrickWithItem;
QuestionBlock:
    JSR(GetAreaObjectID, 117)
    goto DrawQBlk;
BrickWithCoins:
    a = 0x00;
    writeData(BrickCoinTimerFlag, a);
BrickWithItem:
    JSR(GetAreaObjectID, 118)
    writeData(0x07, y);
    a = 0x00;
    y = M(AreaType);
    --y;
    if (z)
        goto BWithL;
    a = 0x05;
BWithL:
    c = 0;
    a += M(0x07);
    y = a;
DrawQBlk:
    a = M(BrickQBlockMetatiles + y);
    pha();
    JSR(GetLrgObjAttrib, 119)
    goto DrawRow;
GetAreaObjectID:
    a = M(0x00);
    c = 1;
    a -= 0x00;
    y = a;
ExitDecBlock:
    goto Return;

//---------------------------------------------------------------------

Hole_Empty:
    JSR(ChkLrgObjLength, 120)
    if (!c)
        goto NoWhirlP;
    a = M(AreaType);
    if (!z)
        goto NoWhirlP;
    x = M(Whirlpool_Offset);
    JSR(GetAreaObjXPosition, 121)
    c = 1;
    a -= 0x10;
    writeData(Whirlpool_LeftExtent + x, a);
    a = M(CurrentPageLoc);
    a -= 0x00;
    writeData(Whirlpool_PageLoc + x, a);
    ++y;
    ++y;
    a = y;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    writeData(Whirlpool_Length + x, a);
    ++x;
    compare(x, 0x05);
    if (!c)
        goto StrWOffset;
    x = 0x00;
StrWOffset:
    writeData(Whirlpool_Offset, x);
NoWhirlP:
    x = M(AreaType);
    a = M(HoleMetatiles + x);
    x = 0x08;
    y = 0x0f;
RenderUnderPart:
    writeData(AreaObjectHeight, y);
    y = M(MetatileBuffer + x);
    if (z)
        goto DrawThisRow;
    compare(y, 0x17);
    if (z)
        goto WaitOneRow;
    compare(y, 0x1a);
    if (z)
        goto WaitOneRow;
    compare(y, 0xc0);
    if (z)
        goto DrawThisRow;
    compare(y, 0xc0);
    if (c)
        goto WaitOneRow;
    compare(y, 0x54);
    if (!z)
        goto DrawThisRow;
    compare(a, 0x50);
    if (z)
        goto WaitOneRow;
DrawThisRow:
    writeData(MetatileBuffer + x, a);
WaitOneRow:
    ++x;
    compare(x, 0x0d);
    if (c)
        goto ExitUPartR;
    y = M(AreaObjectHeight);
    --y;
    if (!n)
        goto RenderUnderPart;
ExitUPartR:
    goto Return;

//---------------------------------------------------------------------

ChkLrgObjLength:
    JSR(GetLrgObjAttrib, 122)
ChkLrgObjFixedLength:
    a = M(AreaObjectLength + x);
    c = 0;
    if (!n)
        goto LenSet;
    a = y;
    writeData(AreaObjectLength + x, a);
    c = 1;
LenSet:
    goto Return;

//---------------------------------------------------------------------

GetLrgObjAttrib:
    y = M(AreaObjOffsetBuffer + x);
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00001111);
    writeData(0x07, a);
    ++y;
    a = M(W(AreaData) + y);
    a &= BOOST_BINARY(00001111);
    y = a;
    goto Return;

//---------------------------------------------------------------------

GetAreaObjXPosition:
    a = M(CurrentColumnPos);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    goto Return;

//---------------------------------------------------------------------

GetAreaObjYPosition:
    a = M(0x07);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 32;
    goto Return;

//---------------------------------------------------------------------

GetBlockBufferAddr:
    pha();
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    y = a;
    a = M(BlockBufferAddr + 2 + y);
    writeData(0x07, a);
    pla();
    a &= BOOST_BINARY(00001111);
    c = 0;
    a += M(BlockBufferAddr + y);
    writeData(0x06, a);
    goto Return;

//---------------------------------------------------------------------

LoadAreaPointer:
    JSR(FindAreaPointer, 123)
    writeData(AreaPointer, a);
GetAreaType:
    a &= BOOST_BINARY(01100000);
    a <<= 1;
    a.rol();
    a.rol();
    a.rol();
    writeData(AreaType, a);
    goto Return;

//---------------------------------------------------------------------

FindAreaPointer:
    y = M(WorldNumber);
    a = M(WorldAddrOffsets + y);
    c = 0;
    a += M(AreaNumber);
    y = a;
    a = M(AreaAddrOffsets + y);
    goto Return;

//---------------------------------------------------------------------

GetAreaDataAddrs:
    a = M(AreaPointer);
    JSR(GetAreaType, 124)
    y = a;
    a = M(AreaPointer);
    a &= BOOST_BINARY(00011111);
    writeData(AreaAddrsLOffset, a);
    a = M(EnemyAddrHOffsets + y);
    c = 0;
    a += M(AreaAddrsLOffset);
    y = a;
    a = M(EnemyDataAddrLow + y);
    writeData(EnemyDataLow, a);
    a = M(EnemyDataAddrHigh + y);
    writeData(EnemyDataHigh, a);
    y = M(AreaType);
    a = M(AreaDataHOffsets + y);
    c = 0;
    a += M(AreaAddrsLOffset);
    y = a;
    a = M(AreaDataAddrLow + y);
    writeData(AreaDataLow, a);
    a = M(AreaDataAddrHigh + y);
    writeData(AreaDataHigh, a);
    y = 0x00;
    a = M(W(AreaData) + y);
    pha();
    a &= BOOST_BINARY(00000111);
    compare(a, 0x04);
    if (!c)
        goto StoreFore;
    writeData(BackgroundColorCtrl, a);
    a = 0x00;
StoreFore:
    writeData(ForegroundScenery, a);
    pla();
    pha();
    a &= BOOST_BINARY(00111000);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(PlayerEntranceCtrl, a);
    pla();
    a &= BOOST_BINARY(11000000);
    c = 0;
    a.rol();
    a.rol();
    a.rol();
    writeData(GameTimerSetting, a);
    ++y;
    a = M(W(AreaData) + y);
    pha();
    a &= BOOST_BINARY(00001111);
    writeData(TerrainControl, a);
    pla();
    pha();
    a &= BOOST_BINARY(00110000);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(BackgroundScenery, a);
    pla();
    a &= BOOST_BINARY(11000000);
    c = 0;
    a.rol();
    a.rol();
    a.rol();
    compare(a, BOOST_BINARY(00000011));
    if (!z)
        goto StoreStyle;
    writeData(CloudTypeOverride, a);
    a = 0x00;
StoreStyle:
    writeData(AreaStyle, a);
    a = M(AreaDataLow);
    c = 0;
    a += 0x02;
    writeData(AreaDataLow, a);
    a = M(AreaDataHigh);
    a += 0x00;
    writeData(AreaDataHigh, a);
    goto Return;

//---------------------------------------------------------------------

GameMode:
    a = M(OperMode_Task);
    switch(a)
        {
    case 0:
        goto InitializeArea;
    case 1:
        goto ScreenRoutines;
    case 2:
        goto SecondaryGameSetup;
    case 3:
        goto GameCoreRoutine;
    }
GameCoreRoutine:
    x = M(CurrentPlayer);
    a = M(SavedJoypadBits + x);
    writeData(SavedJoypadBits, a);
    JSR(GameRoutines, 125)
    a = M(OperMode_Task);
    compare(a, 0x03);
    if (c)
        goto GameEngine;
    goto Return;

//---------------------------------------------------------------------

GameEngine:
    JSR(ProcFireball_Bubble, 126)
    x = 0x00;
ProcELoop:
    writeData(ObjectOffset, x);
    JSR(EnemiesAndLoopsCore, 127)
    JSR(FloateyNumbersRoutine, 128)
    ++x;
    compare(x, 0x06);
    if (!z)
        goto ProcELoop;
    JSR(GetPlayerOffscreenBits, 129)
    JSR(RelativePlayerPosition, 130)
    JSR(PlayerGfxHandler, 131)
    JSR(BlockObjMT_Updater, 132)
    x = 0x01;
    writeData(ObjectOffset, x);
    JSR(BlockObjectsCore, 133)
    --x;
    writeData(ObjectOffset, x);
    JSR(BlockObjectsCore, 134)
    JSR(MiscObjectsCore, 135)
    JSR(ProcessCannons, 136)
    JSR(ProcessWhirlpools, 137)
    JSR(FlagpoleRoutine, 138)
    JSR(RunGameTimer, 139)
    JSR(ColorRotation, 140)
    a = M(Player_Y_HighPos);
    compare(a, 0x02);
    if (!n)
        goto NoChgMus;
    a = M(StarInvincibleTimer);
    if (z)
        goto ClrPlrPal;
    compare(a, 0x04);
    if (!z)
        goto NoChgMus;
    a = M(IntervalTimerControl);
    if (!z)
        goto NoChgMus;
    JSR(GetAreaMusic, 141)
NoChgMus:
    y = M(StarInvincibleTimer);
    a = M(FrameCounter);
    compare(y, 0x08);
    if (c)
        goto CycleTwo;
    a >>= 1;
    a >>= 1;
CycleTwo:
    a >>= 1;
    JSR(CyclePlayerPalette, 142)
    goto SaveAB;
ClrPlrPal:
    JSR(ResetPalStar, 143)
SaveAB:
    a = M(A_B_Buttons);
    writeData(PreviousA_B_Buttons, a);
    a = 0x00;
    writeData(Left_Right_Buttons, a);
UpdScrollVar:
    a = M(VRAM_Buffer_AddrCtrl);
    compare(a, 0x06);
    if (z)
        goto ExitEng;
    a = M(AreaParserTaskNum);
    if (!z)
        goto RunParser;
    a = M(ScrollThirtyTwo);
    compare(a, 0x20);
    if (n)
        goto ExitEng;
    a = M(ScrollThirtyTwo);
    a -= 0x20;
    writeData(ScrollThirtyTwo, a);
    a = 0x00;
    writeData(VRAM_Buffer2_Offset, a);
RunParser:
    JSR(AreaParserTaskHandler, 144)
ExitEng:
    goto Return;

//---------------------------------------------------------------------

ScrollHandler:
    a = M(Player_X_Scroll);
    c = 0;
    a += M(Platform_X_Scroll);
    writeData(Player_X_Scroll, a);
    a = M(ScrollLock);
    if (!z)
        goto InitScrlAmt;
    a = M(Player_Pos_ForScroll);
    compare(a, 0x50);
    if (!c)
        goto InitScrlAmt;
    a = M(SideCollisionTimer);
    if (!z)
        goto InitScrlAmt;
    y = M(Player_X_Scroll);
    --y;
    if (n)
        goto InitScrlAmt;
    ++y;
    compare(y, 0x02);
    if (!c)
        goto ChkNearMid;
    --y;
ChkNearMid:
    a = M(Player_Pos_ForScroll);
    compare(a, 0x70);
    if (!c)
        goto ScrollScreen;
    y = M(Player_X_Scroll);
ScrollScreen:
    a = y;
    writeData(ScrollAmount, a);
    c = 0;
    a += M(ScrollThirtyTwo);
    writeData(ScrollThirtyTwo, a);
    a = y;
    c = 0;
    a += M(ScreenLeft_X_Pos);
    writeData(ScreenLeft_X_Pos, a);
    writeData(HorizontalScroll, a);
    a = M(ScreenLeft_PageLoc);
    a += 0x00;
    writeData(ScreenLeft_PageLoc, a);
    a &= 0x01;
    writeData(0x00, a);
    a = M(Mirror_PPU_CTRL_REG1);
    a &= BOOST_BINARY(11111110);
    a |= M(0x00);
    writeData(Mirror_PPU_CTRL_REG1, a);
    JSR(GetScreenPosition, 145)
    a = 0x08;
    writeData(ScrollIntervalTimer, a);
    goto ChkPOffscr;
InitScrlAmt:
    a = 0x00;
    writeData(ScrollAmount, a);
ChkPOffscr:
    x = 0x00;
    JSR(GetXOffscreenBits, 146)
    writeData(0x00, a);
    y = 0x00;
    a <<= 1;
    if (c)
        goto KeepOnscr;
    ++y;
    a = M(0x00);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto InitPlatScrl;
KeepOnscr:
    a = M(ScreenEdge_X_Pos + y);
    c = 1;
    a -= M(X_SubtracterData + y);
    writeData(Player_X_Position, a);
    a = M(ScreenEdge_PageLoc + y);
    a -= 0x00;
    writeData(Player_PageLoc, a);
    a = M(Left_Right_Buttons);
    compare(a, M(OffscrJoypadBitsData + y));
    if (z)
        goto InitPlatScrl;
    a = 0x00;
    writeData(Player_X_Speed, a);
InitPlatScrl:
    a = 0x00;
    writeData(Platform_X_Scroll, a);
    goto Return;

//---------------------------------------------------------------------

GetScreenPosition:
    a = M(ScreenLeft_X_Pos);
    c = 0;
    a += 0xff;
    writeData(ScreenRight_X_Pos, a);
    a = M(ScreenLeft_PageLoc);
    a += 0x00;
    writeData(ScreenRight_PageLoc, a);
    goto Return;

//---------------------------------------------------------------------

GameRoutines:
    a = M(GameEngineSubroutine);
    switch(a)
        {
    case 0:
        goto Entrance_GameTimerSetup;
    case 1:
        goto Vine_AutoClimb;
    case 2:
        goto SideExitPipeEntry;
    case 3:
        goto VerticalPipeEntry;
    case 4:
        goto FlagpoleSlide;
    case 5:
        goto PlayerEndLevel;
    case 6:
        goto PlayerLoseLife;
    case 7:
        goto PlayerEntrance;
    case 8:
        goto PlayerCtrlRoutine;
    case 9:
        goto PlayerChangeSize;
    case 10:
        goto PlayerInjuryBlink;
    case 11:
        goto PlayerDeath;
    case 12:
        goto PlayerFireFlower;
    }
PlayerEntrance:
    a = M(AltEntranceControl);
    compare(a, 0x02);
    if (z)
        goto EntrMode2;
    a = 0x00;
    y = M(Player_Y_Position);
    compare(y, 0x30);
    if (!c)
        goto AutoControlPlayer;
    a = M(PlayerEntranceCtrl);
    compare(a, 0x06);
    if (z)
        goto ChkBehPipe;
    compare(a, 0x07);
    if (!z)
        goto PlayerRdy;
ChkBehPipe:
    a = M(Player_SprAttrib);
    if (!z)
        goto IntroEntr;
    a = 0x01;
    goto AutoControlPlayer;
IntroEntr:
    JSR(EnterSidePipe, 147)
    --M(ChangeAreaTimer);
    if (!z)
        goto ExitEntr;
    ++M(DisableIntermediate);
    goto NextArea;
EntrMode2:
    a = M(JoypadOverride);
    if (!z)
        goto VineEntr;
    a = 0xff;
    JSR(MovePlayerYAxis, 148)
    a = M(Player_Y_Position);
    compare(a, 0x91);
    if (!c)
        goto PlayerRdy;
    goto Return;

//---------------------------------------------------------------------

VineEntr:
    a = M(VineHeight);
    compare(a, 0x60);
    if (!z)
        goto ExitEntr;
    a = M(Player_Y_Position);
    compare(a, 0x99);
    y = 0x00;
    a = 0x01;
    if (!c)
        goto OffVine;
    a = 0x03;
    writeData(Player_State, a);
    ++y;
    a = 0x08;
    writeData(Block_Buffer_1 + 0xb4, a);
OffVine:
    writeData(DisableCollisionDet, y);
    JSR(AutoControlPlayer, 149)
    a = M(Player_X_Position);
    compare(a, 0x48);
    if (!c)
        goto ExitEntr;
PlayerRdy:
    a = 0x08;
    writeData(GameEngineSubroutine, a);
    a = 0x01;
    writeData(PlayerFacingDir, a);
    a >>= 1;
    writeData(AltEntranceControl, a);
    writeData(DisableCollisionDet, a);
    writeData(JoypadOverride, a);
ExitEntr:
    goto Return;

//---------------------------------------------------------------------

AutoControlPlayer:
    writeData(SavedJoypadBits, a);
PlayerCtrlRoutine:
    a = M(GameEngineSubroutine);
    compare(a, 0x0b);
    if (z)
        goto SizeChk;
    a = M(AreaType);
    if (!z)
        goto SaveJoyp;
    y = M(Player_Y_HighPos);
    --y;
    if (!z)
        goto DisJoyp;
    a = M(Player_Y_Position);
    compare(a, 0xd0);
    if (!c)
        goto SaveJoyp;
DisJoyp:
    a = 0x00;
    writeData(SavedJoypadBits, a);
SaveJoyp:
    a = M(SavedJoypadBits);
    a &= BOOST_BINARY(11000000);
    writeData(A_B_Buttons, a);
    a = M(SavedJoypadBits);
    a &= BOOST_BINARY(00000011);
    writeData(Left_Right_Buttons, a);
    a = M(SavedJoypadBits);
    a &= BOOST_BINARY(00001100);
    writeData(Up_Down_Buttons, a);
    a &= BOOST_BINARY(00000100);
    if (z)
        goto SizeChk;
    a = M(Player_State);
    if (!z)
        goto SizeChk;
    y = M(Left_Right_Buttons);
    if (z)
        goto SizeChk;
    a = 0x00;
    writeData(Left_Right_Buttons, a);
    writeData(Up_Down_Buttons, a);
SizeChk:
    JSR(PlayerMovementSubs, 150)
    y = 0x01;
    a = M(PlayerSize);
    if (!z)
        goto ChkMoveDir;
    y = 0x00;
    a = M(CrouchingFlag);
    if (z)
        goto ChkMoveDir;
    y = 0x02;
ChkMoveDir:
    writeData(Player_BoundBoxCtrl, y);
    a = 0x01;
    y = M(Player_X_Speed);
    if (z)
        goto PlayerSubs;
    if (!n)
        goto SetMoveDir;
    a <<= 1;
SetMoveDir:
    writeData(Player_MovingDir, a);
PlayerSubs:
    JSR(ScrollHandler, 151)
    JSR(GetPlayerOffscreenBits, 152)
    JSR(RelativePlayerPosition, 153)
    x = 0x00;
    JSR(BoundingBoxCore, 154)
    JSR(PlayerBGCollision, 155)
    a = M(Player_Y_Position);
    compare(a, 0x40);
    if (!c)
        goto PlayerHole;
    a = M(GameEngineSubroutine);
    compare(a, 0x05);
    if (z)
        goto PlayerHole;
    compare(a, 0x07);
    if (z)
        goto PlayerHole;
    compare(a, 0x04);
    if (!c)
        goto PlayerHole;
    a = M(Player_SprAttrib);
    a &= BOOST_BINARY(11011111);
    writeData(Player_SprAttrib, a);
PlayerHole:
    a = M(Player_Y_HighPos);
    compare(a, 0x02);
    if (n)
        goto ExitCtrl;
    x = 0x01;
    writeData(ScrollLock, x);
    y = 0x04;
    writeData(0x07, y);
    x = 0x00;
    y = M(GameTimerExpiredFlag);
    if (!z)
        goto HoleDie;
    y = M(CloudTypeOverride);
    if (!z)
        goto ChkHoleX;
HoleDie:
    ++x;
    y = M(GameEngineSubroutine);
    compare(y, 0x0b);
    if (z)
        goto ChkHoleX;
    y = M(DeathMusicLoaded);
    if (!z)
        goto HoleBottom;
    ++y;
    writeData(EventMusicQueue, y);
    writeData(DeathMusicLoaded, y);
HoleBottom:
    y = 0x06;
    writeData(0x07, y);
ChkHoleX:
    compare(a, M(0x07));
    if (n)
        goto ExitCtrl;
    --x;
    if (n)
        goto CloudExit;
    y = M(EventMusicBuffer);
    if (!z)
        goto ExitCtrl;
    a = 0x06;
    writeData(GameEngineSubroutine, a);
ExitCtrl:
    goto Return;

//---------------------------------------------------------------------

CloudExit:
    a = 0x00;
    writeData(JoypadOverride, a);
    JSR(SetEntr, 156)
    ++M(AltEntranceControl);
    goto Return;

//---------------------------------------------------------------------

Vine_AutoClimb:
    a = M(Player_Y_HighPos);
    if (!z)
        goto AutoClimb;
    a = M(Player_Y_Position);
    compare(a, 0xe4);
    if (!c)
        goto SetEntr;
AutoClimb:
    a = BOOST_BINARY(00001000);
    writeData(JoypadOverride, a);
    y = 0x03;
    writeData(Player_State, y);
    goto AutoControlPlayer;
SetEntr:
    a = 0x02;
    writeData(AltEntranceControl, a);
    goto ChgAreaMode;
VerticalPipeEntry:
    a = 0x01;
    JSR(MovePlayerYAxis, 157)
    JSR(ScrollHandler, 158)
    y = 0x00;
    a = M(WarpZoneControl);
    if (!z)
        goto ChgAreaPipe;
    ++y;
    a = M(AreaType);
    compare(a, 0x03);
    if (!z)
        goto ChgAreaPipe;
    ++y;
    goto ChgAreaPipe;
MovePlayerYAxis:
    c = 0;
    a += M(Player_Y_Position);
    writeData(Player_Y_Position, a);
    goto Return;

//---------------------------------------------------------------------

SideExitPipeEntry:
    JSR(EnterSidePipe, 159)
    y = 0x02;
ChgAreaPipe:
    --M(ChangeAreaTimer);
    if (!z)
        goto ExitCAPipe;
    writeData(AltEntranceControl, y);
ChgAreaMode:
    ++M(DisableScreenFlag);
    a = 0x00;
    writeData(OperMode_Task, a);
    writeData(Sprite0HitDetectFlag, a);
ExitCAPipe:
    goto Return;

//---------------------------------------------------------------------

EnterSidePipe:
    a = 0x08;
    writeData(Player_X_Speed, a);
    y = 0x01;
    a = M(Player_X_Position);
    a &= BOOST_BINARY(00001111);
    if (!z)
        goto RightPipe;
    writeData(Player_X_Speed, a);
    y = a;
RightPipe:
    a = y;
    JSR(AutoControlPlayer, 160)
    goto Return;

//---------------------------------------------------------------------

PlayerChangeSize:
    a = M(TimerControl);
    compare(a, 0xf8);
    if (!z)
        goto EndChgSize;
    goto InitChangeSize;
EndChgSize:
    compare(a, 0xc4);
    if (!z)
        goto ExitChgSize;
    JSR(DonePlayerTask, 161)
ExitChgSize:
    goto Return;

//---------------------------------------------------------------------

PlayerInjuryBlink:
    a = M(TimerControl);
    compare(a, 0xf0);
    if (c)
        goto ExitBlink;
    compare(a, 0xc8);
    if (z)
        goto DonePlayerTask;
    goto PlayerCtrlRoutine;
ExitBlink:
    if (!z)
        goto ExitBoth;
InitChangeSize:
    y = M(PlayerChangeSizeFlag);
    if (!z)
        goto ExitBoth;
    writeData(PlayerAnimCtrl, y);
    ++M(PlayerChangeSizeFlag);
    a = M(PlayerSize);
    a ^= 0x01;
    writeData(PlayerSize, a);
ExitBoth:
    goto Return;

//---------------------------------------------------------------------

PlayerDeath:
    a = M(TimerControl);
    compare(a, 0xf0);
    if (c)
        goto ExitDeath;
    goto PlayerCtrlRoutine;
DonePlayerTask:
    a = 0x00;
    writeData(TimerControl, a);
    a = 0x08;
    writeData(GameEngineSubroutine, a);
    goto Return;

//---------------------------------------------------------------------

PlayerFireFlower:
    a = M(TimerControl);
    compare(a, 0xc0);
    if (z)
        goto ResetPalFireFlower;
    a = M(FrameCounter);
    a >>= 1;
    a >>= 1;
CyclePlayerPalette:
    a &= 0x03;
    writeData(0x00, a);
    a = M(Player_SprAttrib);
    a &= BOOST_BINARY(11111100);
    a |= M(0x00);
    writeData(Player_SprAttrib, a);
    goto Return;

//---------------------------------------------------------------------

ResetPalFireFlower:
    JSR(DonePlayerTask, 162)
ResetPalStar:
    a = M(Player_SprAttrib);
    a &= BOOST_BINARY(11111100);
    writeData(Player_SprAttrib, a);
    goto Return;

//---------------------------------------------------------------------

ExitDeath:
    goto Return;

//---------------------------------------------------------------------

FlagpoleSlide:
    a = M(Enemy_ID + 5);
    compare(a, FlagpoleFlagObject);
    if (!z)
        goto NoFPObj;
    a = M(FlagpoleSoundQueue);
    writeData(Square1SoundQueue, a);
    a = 0x00;
    writeData(FlagpoleSoundQueue, a);
    y = M(Player_Y_Position);
    compare(y, 0x9e);
    if (c)
        goto SlidePlayer;
    a = 0x04;
SlidePlayer:
    goto AutoControlPlayer;
NoFPObj:
    ++M(GameEngineSubroutine);
    goto Return;

//---------------------------------------------------------------------

PlayerEndLevel:
    a = 0x01;
    JSR(AutoControlPlayer, 163)
    a = M(Player_Y_Position);
    compare(a, 0xae);
    if (!c)
        goto ChkStop;
    a = M(ScrollLock);
    if (z)
        goto ChkStop;
    a = EndOfLevelMusic;
    writeData(EventMusicQueue, a);
    a = 0x00;
    writeData(ScrollLock, a);
ChkStop:
    a = M(Player_CollisionBits);
    a >>= 1;
    if (c)
        goto RdyNextA;
    a = M(StarFlagTaskControl);
    if (!z)
        goto InCastle;
    ++M(StarFlagTaskControl);
InCastle:
    a = BOOST_BINARY(00100000);
    writeData(Player_SprAttrib, a);
RdyNextA:
    a = M(StarFlagTaskControl);
    compare(a, 0x05);
    if (!z)
        goto ExitNA;
    ++M(LevelNumber);
    a = M(LevelNumber);
    compare(a, 0x03);
    if (!z)
        goto NextArea;
    y = M(WorldNumber);
    a = M(CoinTallyFor1Ups);
    compare(a, M(Hidden1UpCoinAmts + y));
    if (!c)
        goto NextArea;
    ++M(Hidden1UpFlag);
NextArea:
    ++M(AreaNumber);
    JSR(LoadAreaPointer, 164)
    ++M(FetchNewGameTimerFlag);
    JSR(ChgAreaMode, 165)
    writeData(HalfwayPage, a);
    a = Silence;
    writeData(EventMusicQueue, a);
ExitNA:
    goto Return;

//---------------------------------------------------------------------

PlayerMovementSubs:
    a = 0x00;
    y = M(PlayerSize);
    if (!z)
        goto SetCrouch;
    a = M(Player_State);
    if (!z)
        goto ProcMove;
    a = M(Up_Down_Buttons);
    a &= BOOST_BINARY(00000100);
SetCrouch:
    writeData(CrouchingFlag, a);
ProcMove:
    JSR(PlayerPhysicsSub, 166)
    a = M(PlayerChangeSizeFlag);
    if (!z)
        goto NoMoveSub;
    a = M(Player_State);
    compare(a, 0x03);
    if (z)
        goto MoveSubs;
    y = 0x18;
    writeData(ClimbSideTimer, y);
MoveSubs:
    switch(a)
        {
    case 0:
        goto OnGroundStateSub;
    case 1:
        goto JumpSwimSub;
    case 2:
        goto FallingSub;
    case 3:
        goto ClimbingSub;
    }
NoMoveSub:
    goto Return;

//---------------------------------------------------------------------

OnGroundStateSub:
    JSR(GetPlayerAnimSpeed, 167)
    a = M(Left_Right_Buttons);
    if (z)
        goto GndMove;
    writeData(PlayerFacingDir, a);
GndMove:
    JSR(ImposeFriction, 168)
    JSR(MovePlayerHorizontally, 169)
    writeData(Player_X_Scroll, a);
    goto Return;

//---------------------------------------------------------------------

FallingSub:
    a = M(VerticalForceDown);
    writeData(VerticalForce, a);
    goto LRAir;
JumpSwimSub:
    y = M(Player_Y_Speed);
    if (!n)
        goto DumpFall;
    a = M(A_B_Buttons);
    a &= A_Button;
    a &= M(PreviousA_B_Buttons);
    if (!z)
        goto ProcSwim;
    a = M(JumpOrigin_Y_Position);
    c = 1;
    a -= M(Player_Y_Position);
    compare(a, M(DiffToHaltJump));
    if (!c)
        goto ProcSwim;
DumpFall:
    a = M(VerticalForceDown);
    writeData(VerticalForce, a);
ProcSwim:
    a = M(SwimmingFlag);
    if (z)
        goto LRAir;
    JSR(GetPlayerAnimSpeed, 170)
    a = M(Player_Y_Position);
    compare(a, 0x14);
    if (c)
        goto LRWater;
    a = 0x18;
    writeData(VerticalForce, a);
LRWater:
    a = M(Left_Right_Buttons);
    if (z)
        goto LRAir;
    writeData(PlayerFacingDir, a);
LRAir:
    a = M(Left_Right_Buttons);
    if (z)
        goto JSMove;
    JSR(ImposeFriction, 171)
JSMove:
    JSR(MovePlayerHorizontally, 172)
    writeData(Player_X_Scroll, a);
    a = M(GameEngineSubroutine);
    compare(a, 0x0b);
    if (!z)
        goto ExitMov1;
    a = 0x28;
    writeData(VerticalForce, a);
ExitMov1:
    goto MovePlayerVertically;
ClimbingSub:
    a = M(Player_YMF_Dummy);
    c = 0;
    a += M(Player_Y_MoveForce);
    writeData(Player_YMF_Dummy, a);
    y = 0x00;
    a = M(Player_Y_Speed);
    if (!n)
        goto MoveOnVine;
    --y;
MoveOnVine:
    writeData(0x00, y);
    a += M(Player_Y_Position);
    writeData(Player_Y_Position, a);
    a = M(Player_Y_HighPos);
    a += M(0x00);
    writeData(Player_Y_HighPos, a);
    a = M(Left_Right_Buttons);
    a &= M(Player_CollisionBits);
    if (z)
        goto InitCSTimer;
    y = M(ClimbSideTimer);
    if (!z)
        goto ExitCSub;
    y = 0x18;
    writeData(ClimbSideTimer, y);
    x = 0x00;
    y = M(PlayerFacingDir);
    a >>= 1;
    if (c)
        goto ClimbFD;
    ++x;
    ++x;
ClimbFD:
    --y;
    if (z)
        goto CSetFDir;
    ++x;
CSetFDir:
    a = M(Player_X_Position);
    c = 0;
    a += M(ClimbAdderLow + x);
    writeData(Player_X_Position, a);
    a = M(Player_PageLoc);
    a += M(ClimbAdderHigh + x);
    writeData(Player_PageLoc, a);
    a = M(Left_Right_Buttons);
    a ^= BOOST_BINARY(00000011);
    writeData(PlayerFacingDir, a);
ExitCSub:
    goto Return;

//---------------------------------------------------------------------

InitCSTimer:
    writeData(ClimbSideTimer, a);
    goto Return;

//---------------------------------------------------------------------

PlayerPhysicsSub:
    a = M(Player_State);
    compare(a, 0x03);
    if (!z)
        goto CheckForJumping;
    y = 0x00;
    a = M(Up_Down_Buttons);
    a &= M(Player_CollisionBits);
    if (z)
        goto ProcClimb;
    ++y;
    a &= BOOST_BINARY(00001000);
    if (!z)
        goto ProcClimb;
    ++y;
ProcClimb:
    x = M(Climb_Y_MForceData + y);
    writeData(Player_Y_MoveForce, x);
    a = 0x08;
    x = M(Climb_Y_SpeedData + y);
    writeData(Player_Y_Speed, x);
    if (n)
        goto SetCAnim;
    a >>= 1;
SetCAnim:
    writeData(PlayerAnimTimerSet, a);
    goto Return;

//---------------------------------------------------------------------

CheckForJumping:
    a = M(JumpspringAnimCtrl);
    if (!z)
        goto NoJump;
    a = M(A_B_Buttons);
    a &= A_Button;
    if (z)
        goto NoJump;
    a &= M(PreviousA_B_Buttons);
    if (z)
        goto ProcJumping;
NoJump:
    goto X_Physics;
ProcJumping:
    a = M(Player_State);
    if (z)
        goto InitJS;
    a = M(SwimmingFlag);
    if (z)
        goto NoJump;
    a = M(JumpSwimTimer);
    if (!z)
        goto InitJS;
    a = M(Player_Y_Speed);
    if (!n)
        goto InitJS;
    goto X_Physics;
InitJS:
    a = 0x20;
    writeData(JumpSwimTimer, a);
    y = 0x00;
    writeData(Player_YMF_Dummy, y);
    writeData(Player_Y_MoveForce, y);
    a = M(Player_Y_HighPos);
    writeData(JumpOrigin_Y_HighPos, a);
    a = M(Player_Y_Position);
    writeData(JumpOrigin_Y_Position, a);
    a = 0x01;
    writeData(Player_State, a);
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x09);
    if (!c)
        goto ChkWtr;
    ++y;
    compare(a, 0x10);
    if (!c)
        goto ChkWtr;
    ++y;
    compare(a, 0x19);
    if (!c)
        goto ChkWtr;
    ++y;
    compare(a, 0x1c);
    if (!c)
        goto ChkWtr;
    ++y;
ChkWtr:
    a = 0x01;
    writeData(DiffToHaltJump, a);
    a = M(SwimmingFlag);
    if (z)
        goto GetYPhy;
    y = 0x05;
    a = M(Whirlpool_Flag);
    if (z)
        goto GetYPhy;
    ++y;
GetYPhy:
    a = M(JumpMForceData + y);
    writeData(VerticalForce, a);
    a = M(FallMForceData + y);
    writeData(VerticalForceDown, a);
    a = M(InitMForceData + y);
    writeData(Player_Y_MoveForce, a);
    a = M(PlayerYSpdData + y);
    writeData(Player_Y_Speed, a);
    a = M(SwimmingFlag);
    if (z)
        goto PJumpSnd;
    a = Sfx_EnemyStomp;
    writeData(Square1SoundQueue, a);
    a = M(Player_Y_Position);
    compare(a, 0x14);
    if (c)
        goto X_Physics;
    a = 0x00;
    writeData(Player_Y_Speed, a);
    goto X_Physics;
PJumpSnd:
    a = Sfx_BigJump;
    y = M(PlayerSize);
    if (z)
        goto SJumpSnd;
    a = Sfx_SmallJump;
SJumpSnd:
    writeData(Square1SoundQueue, a);
X_Physics:
    y = 0x00;
    writeData(0x00, y);
    a = M(Player_State);
    if (z)
        goto ProcPRun;
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x19);
    if (c)
        goto GetXPhy;
    if (!c)
        goto ChkRFast;
ProcPRun:
    ++y;
    a = M(AreaType);
    if (z)
        goto ChkRFast;
    --y;
    a = M(Left_Right_Buttons);
    compare(a, M(Player_MovingDir));
    if (!z)
        goto ChkRFast;
    a = M(A_B_Buttons);
    a &= B_Button;
    if (!z)
        goto SetRTmr;
    a = M(RunningTimer);
    if (!z)
        goto GetXPhy;
ChkRFast:
    ++y;
    ++M(0x00);
    a = M(RunningSpeed);
    if (!z)
        goto FastXSp;
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x21);
    if (!c)
        goto GetXPhy;
FastXSp:
    ++M(0x00);
    goto GetXPhy;
SetRTmr:
    a = 0x0a;
    writeData(RunningTimer, a);
GetXPhy:
    a = M(MaxLeftXSpdData + y);
    writeData(MaximumLeftSpeed, a);
    a = M(GameEngineSubroutine);
    compare(a, 0x07);
    if (!z)
        goto GetXPhy2;
    y = 0x03;
GetXPhy2:
    a = M(MaxRightXSpdData + y);
    writeData(MaximumRightSpeed, a);
    y = M(0x00);
    a = M(FrictionData + y);
    writeData(FrictionAdderLow, a);
    a = 0x00;
    writeData(FrictionAdderHigh, a);
    a = M(PlayerFacingDir);
    compare(a, M(Player_MovingDir));
    if (z)
        goto ExitPhy;
    M(FrictionAdderLow) <<= 1;
    M(FrictionAdderHigh).rol();
ExitPhy:
    goto Return;

//---------------------------------------------------------------------

GetPlayerAnimSpeed:
    y = 0x00;
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x1c);
    if (c)
        goto SetRunSpd;
    ++y;
    compare(a, 0x0e);
    if (c)
        goto ChkSkid;
    ++y;
ChkSkid:
    a = M(SavedJoypadBits);
    a &= BOOST_BINARY(01111111);
    if (z)
        goto SetAnimSpd;
    a &= 0x03;
    compare(a, M(Player_MovingDir));
    if (!z)
        goto ProcSkid;
    a = 0x00;
SetRunSpd:
    writeData(RunningSpeed, a);
    goto SetAnimSpd;
ProcSkid:
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x0b);
    if (c)
        goto SetAnimSpd;
    a = M(PlayerFacingDir);
    writeData(Player_MovingDir, a);
    a = 0x00;
    writeData(Player_X_Speed, a);
    writeData(Player_X_MoveForce, a);
SetAnimSpd:
    a = M(PlayerAnimTmrData + y);
    writeData(PlayerAnimTimerSet, a);
    goto Return;

//---------------------------------------------------------------------

ImposeFriction:
    a &= M(Player_CollisionBits);
    compare(a, 0x00);
    if (!z)
        goto JoypFrict;
    a = M(Player_X_Speed);
    if (z)
        goto SetAbsSpd;
    if (!n)
        goto RghtFrict;
    if (n)
        goto LeftFrict;
JoypFrict:
    a >>= 1;
    if (!c)
        goto RghtFrict;
LeftFrict:
    a = M(Player_X_MoveForce);
    c = 0;
    a += M(FrictionAdderLow);
    writeData(Player_X_MoveForce, a);
    a = M(Player_X_Speed);
    a += M(FrictionAdderHigh);
    writeData(Player_X_Speed, a);
    compare(a, M(MaximumRightSpeed));
    if (n)
        goto XSpdSign;
    a = M(MaximumRightSpeed);
    writeData(Player_X_Speed, a);
    goto SetAbsSpd;
RghtFrict:
    a = M(Player_X_MoveForce);
    c = 1;
    a -= M(FrictionAdderLow);
    writeData(Player_X_MoveForce, a);
    a = M(Player_X_Speed);
    a -= M(FrictionAdderHigh);
    writeData(Player_X_Speed, a);
    compare(a, M(MaximumLeftSpeed));
    if (!n)
        goto XSpdSign;
    a = M(MaximumLeftSpeed);
    writeData(Player_X_Speed, a);
XSpdSign:
    compare(a, 0x00);
    if (!n)
        goto SetAbsSpd;
    a ^= 0xff;
    c = 0;
    a += 0x01;
SetAbsSpd:
    writeData(Player_XSpeedAbsolute, a);
    goto Return;

//---------------------------------------------------------------------

ProcFireball_Bubble:
    a = M(PlayerStatus);
    compare(a, 0x02);
    if (!c)
        goto ProcAirBubbles;
    a = M(A_B_Buttons);
    a &= B_Button;
    if (z)
        goto ProcFireballs;
    a &= M(PreviousA_B_Buttons);
    if (!z)
        goto ProcFireballs;
    a = M(FireballCounter);
    a &= BOOST_BINARY(00000001);
    x = a;
    a = M(Fireball_State + x);
    if (!z)
        goto ProcFireballs;
    y = M(Player_Y_HighPos);
    --y;
    if (!z)
        goto ProcFireballs;
    a = M(CrouchingFlag);
    if (!z)
        goto ProcFireballs;
    a = M(Player_State);
    compare(a, 0x03);
    if (z)
        goto ProcFireballs;
    a = Sfx_Fireball;
    writeData(Square1SoundQueue, a);
    a = 0x02;
    writeData(Fireball_State + x, a);
    y = M(PlayerAnimTimerSet);
    writeData(FireballThrowingTimer, y);
    --y;
    writeData(PlayerAnimTimer, y);
    ++M(FireballCounter);
ProcFireballs:
    x = 0x00;
    JSR(FireballObjCore, 173)
    x = 0x01;
    JSR(FireballObjCore, 174)
ProcAirBubbles:
    a = M(AreaType);
    if (!z)
        goto BublExit;
    x = 0x02;
BublLoop:
    writeData(ObjectOffset, x);
    JSR(BubbleCheck, 175)
    JSR(RelativeBubblePosition, 176)
    JSR(GetBubbleOffscreenBits, 177)
    JSR(DrawBubble, 178)
    --x;
    if (!n)
        goto BublLoop;
BublExit:
    goto Return;

//---------------------------------------------------------------------

FireballObjCore:
    writeData(ObjectOffset, x);
    a = M(Fireball_State + x);
    a <<= 1;
    if (c)
        goto FireballExplosion;
    y = M(Fireball_State + x);
    if (z)
        goto NoFBall;
    --y;
    if (z)
        goto RunFB;
    a = M(Player_X_Position);
    a += 0x04;
    writeData(Fireball_X_Position + x, a);
    a = M(Player_PageLoc);
    a += 0x00;
    writeData(Fireball_PageLoc + x, a);
    a = M(Player_Y_Position);
    writeData(Fireball_Y_Position + x, a);
    a = 0x01;
    writeData(Fireball_Y_HighPos + x, a);
    y = M(PlayerFacingDir);
    --y;
    a = M(FireballXSpdData + y);
    writeData(Fireball_X_Speed + x, a);
    a = 0x04;
    writeData(Fireball_Y_Speed + x, a);
    a = 0x07;
    writeData(Fireball_BoundBoxCtrl + x, a);
    --M(Fireball_State + x);
RunFB:
    a = x;
    c = 0;
    a += 0x07;
    x = a;
    a = 0x50;
    writeData(0x00, a);
    a = 0x03;
    writeData(0x02, a);
    a = 0x00;
    JSR(ImposeGravity, 179)
    JSR(MoveObjectHorizontally, 180)
    x = M(ObjectOffset);
    JSR(RelativeFireballPosition, 181)
    JSR(GetFireballOffscreenBits, 182)
    JSR(GetFireballBoundBox, 183)
    JSR(FireballBGCollision, 184)
    a = M(FBall_OffscreenBits);
    a &= BOOST_BINARY(11001100);
    if (!z)
        goto EraseFB;
    JSR(FireballEnemyCollision, 185)
    goto DrawFireball;
EraseFB:
    a = 0x00;
    writeData(Fireball_State + x, a);
NoFBall:
    goto Return;

//---------------------------------------------------------------------

FireballExplosion:
    JSR(RelativeFireballPosition, 186)
    goto DrawExplosion_Fireball;
BubbleCheck:
    a = M(PseudoRandomBitReg + 1 + x);
    a &= 0x01;
    writeData(0x07, a);
    a = M(Bubble_Y_Position + x);
    compare(a, 0xf8);
    if (!z)
        goto MoveBubl;
    a = M(AirBubbleTimer);
    if (!z)
        goto ExitBubl;
SetupBubble:
    y = 0x00;
    a = M(PlayerFacingDir);
    a >>= 1;
    if (!c)
        goto PosBubl;
    y = 0x08;
PosBubl:
    a = y;
    a += M(Player_X_Position);
    writeData(Bubble_X_Position + x, a);
    a = M(Player_PageLoc);
    a += 0x00;
    writeData(Bubble_PageLoc + x, a);
    a = M(Player_Y_Position);
    c = 0;
    a += 0x08;
    writeData(Bubble_Y_Position + x, a);
    a = 0x01;
    writeData(Bubble_Y_HighPos + x, a);
    y = M(0x07);
    a = M(BubbleTimerData + y);
    writeData(AirBubbleTimer, a);
MoveBubl:
    y = M(0x07);
    a = M(Bubble_YMF_Dummy + x);
    c = 1;
    a -= M(Bubble_MForceData + y);
    writeData(Bubble_YMF_Dummy + x, a);
    a = M(Bubble_Y_Position + x);
    a -= 0x00;
    compare(a, 0x20);
    if (c)
        goto Y_Bubl;
    a = 0xf8;
Y_Bubl:
    writeData(Bubble_Y_Position + x, a);
ExitBubl:
    goto Return;

//---------------------------------------------------------------------

RunGameTimer:
    a = M(OperMode);
    if (z)
        goto ExGTimer;
    a = M(GameEngineSubroutine);
    compare(a, 0x08);
    if (!c)
        goto ExGTimer;
    compare(a, 0x0b);
    if (z)
        goto ExGTimer;
    a = M(Player_Y_HighPos);
    compare(a, 0x02);
    if (c)
        goto ExGTimer;
    a = M(GameTimerCtrlTimer);
    if (!z)
        goto ExGTimer;
    a = M(GameTimerDisplay);
    a |= M(GameTimerDisplay + 1);
    a |= M(GameTimerDisplay + 2);
    if (z)
        goto TimeUpOn;
    y = M(GameTimerDisplay);
    --y;
    if (!z)
        goto ResGTCtrl;
    a = M(GameTimerDisplay + 1);
    a |= M(GameTimerDisplay + 2);
    if (!z)
        goto ResGTCtrl;
    a = TimeRunningOutMusic;
    writeData(EventMusicQueue, a);
ResGTCtrl:
    a = 0x18;
    writeData(GameTimerCtrlTimer, a);
    y = 0x23;
    a = 0xff;
    writeData(DigitModifier + 5, a);
    JSR(DigitsMathRoutine, 187)
    a = 0xa4;
    goto PrintStatusBarNumbers;
TimeUpOn:
    writeData(PlayerStatus, a);
    JSR(ForceInjury, 188)
    ++M(GameTimerExpiredFlag);
ExGTimer:
    goto Return;

//---------------------------------------------------------------------

WarpZoneObject:
    a = M(ScrollLock);
    if (z)
        goto ExGTimer;
    a = M(Player_Y_Position);
    a &= M(Player_Y_HighPos);
    if (!z)
        goto ExGTimer;
    writeData(ScrollLock, a);
    ++M(WarpZoneControl);
    goto EraseEnemyObject;
ProcessWhirlpools:
    a = M(AreaType);
    if (!z)
        goto ExitWh;
    writeData(Whirlpool_Flag, a);
    a = M(TimerControl);
    if (!z)
        goto ExitWh;
    y = 0x04;
WhLoop:
    a = M(Whirlpool_LeftExtent + y);
    c = 0;
    a += M(Whirlpool_Length + y);
    writeData(0x02, a);
    a = M(Whirlpool_PageLoc + y);
    if (z)
        goto NextWh;
    a += 0x00;
    writeData(0x01, a);
    a = M(Player_X_Position);
    c = 1;
    a -= M(Whirlpool_LeftExtent + y);
    a = M(Player_PageLoc);
    a -= M(Whirlpool_PageLoc + y);
    if (n)
        goto NextWh;
    a = M(0x02);
    c = 1;
    a -= M(Player_X_Position);
    a = M(0x01);
    a -= M(Player_PageLoc);
    if (!n)
        goto WhirlpoolActivate;
NextWh:
    --y;
    if (!n)
        goto WhLoop;
ExitWh:
    goto Return;

//---------------------------------------------------------------------

WhirlpoolActivate:
    a = M(Whirlpool_Length + y);
    a >>= 1;
    writeData(0x00, a);
    a = M(Whirlpool_LeftExtent + y);
    c = 0;
    a += M(0x00);
    writeData(0x01, a);
    a = M(Whirlpool_PageLoc + y);
    a += 0x00;
    writeData(0x00, a);
    a = M(FrameCounter);
    a >>= 1;
    if (!c)
        goto WhPull;
    a = M(0x01);
    c = 1;
    a -= M(Player_X_Position);
    a = M(0x00);
    a -= M(Player_PageLoc);
    if (!n)
        goto LeftWh;
    a = M(Player_X_Position);
    c = 1;
    a -= 0x01;
    writeData(Player_X_Position, a);
    a = M(Player_PageLoc);
    a -= 0x00;
    goto SetPWh;
LeftWh:
    a = M(Player_CollisionBits);
    a >>= 1;
    if (!c)
        goto WhPull;
    a = M(Player_X_Position);
    c = 0;
    a += 0x01;
    writeData(Player_X_Position, a);
    a = M(Player_PageLoc);
    a += 0x00;
SetPWh:
    writeData(Player_PageLoc, a);
WhPull:
    a = 0x10;
    writeData(0x00, a);
    a = 0x01;
    writeData(Whirlpool_Flag, a);
    writeData(0x02, a);
    a >>= 1;
    x = a;
    goto ImposeGravity;
FlagpoleRoutine:
    x = 0x05;
    writeData(ObjectOffset, x);
    a = M(Enemy_ID + x);
    compare(a, FlagpoleFlagObject);
    if (!z)
        goto ExitFlagP;
    a = M(GameEngineSubroutine);
    compare(a, 0x04);
    if (!z)
        goto SkipScore;
    a = M(Player_State);
    compare(a, 0x03);
    if (!z)
        goto SkipScore;
    a = M(Enemy_Y_Position + x);
    compare(a, 0xaa);
    if (c)
        goto GiveFPScr;
    a = M(Player_Y_Position);
    compare(a, 0xa2);
    if (c)
        goto GiveFPScr;
    a = M(Enemy_YMF_Dummy + x);
    a += 0xff;
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    a += 0x01;
    writeData(Enemy_Y_Position + x, a);
    a = M(FlagpoleFNum_YMFDummy);
    c = 1;
    a -= 0xff;
    writeData(FlagpoleFNum_YMFDummy, a);
    a = M(FlagpoleFNum_Y_Pos);
    a -= 0x01;
    writeData(FlagpoleFNum_Y_Pos, a);
SkipScore:
    goto FPGfx;
GiveFPScr:
    y = M(FlagpoleScore);
    a = M(FlagpoleScoreMods + y);
    x = M(FlagpoleScoreDigits + y);
    writeData(DigitModifier + x, a);
    JSR(AddToScore, 189)
    a = 0x05;
    writeData(GameEngineSubroutine, a);
FPGfx:
    JSR(GetEnemyOffscreenBits, 190)
    JSR(RelativeEnemyPosition, 191)
    JSR(FlagpoleGfxHandler, 192)
ExitFlagP:
    goto Return;

//---------------------------------------------------------------------

JumpspringHandler:
    JSR(GetEnemyOffscreenBits, 193)
    a = M(TimerControl);
    if (!z)
        goto DrawJSpr;
    a = M(JumpspringAnimCtrl);
    if (z)
        goto DrawJSpr;
    y = a;
    --y;
    a = y;
    a &= BOOST_BINARY(00000010);
    if (!z)
        goto DownJSpr;
    ++M(Player_Y_Position);
    ++M(Player_Y_Position);
    goto PosJSpr;
DownJSpr:
    --M(Player_Y_Position);
    --M(Player_Y_Position);
PosJSpr:
    a = M(Jumpspring_FixedYPos + x);
    c = 0;
    a += M(Jumpspring_Y_PosData + y);
    writeData(Enemy_Y_Position + x, a);
    compare(y, 0x01);
    if (!c)
        goto BounceJS;
    a = M(A_B_Buttons);
    a &= A_Button;
    if (z)
        goto BounceJS;
    a &= M(PreviousA_B_Buttons);
    if (!z)
        goto BounceJS;
    a = 0xf4;
    writeData(JumpspringForce, a);
BounceJS:
    compare(y, 0x03);
    if (!z)
        goto DrawJSpr;
    a = M(JumpspringForce);
    writeData(Player_Y_Speed, a);
    a = 0x00;
    writeData(JumpspringAnimCtrl, a);
DrawJSpr:
    JSR(RelativeEnemyPosition, 194)
    JSR(EnemyGfxHandler, 195)
    JSR(OffscreenBoundsCheck, 196)
    a = M(JumpspringAnimCtrl);
    if (z)
        goto ExJSpring;
    a = M(JumpspringTimer);
    if (!z)
        goto ExJSpring;
    a = 0x04;
    writeData(JumpspringTimer, a);
    ++M(JumpspringAnimCtrl);
ExJSpring:
    goto Return;

//---------------------------------------------------------------------

Setup_Vine:
    a = VineObject;
    writeData(Enemy_ID + x, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    a = M(Block_PageLoc + y);
    writeData(Enemy_PageLoc + x, a);
    a = M(Block_X_Position + y);
    writeData(Enemy_X_Position + x, a);
    a = M(Block_Y_Position + y);
    writeData(Enemy_Y_Position + x, a);
    y = M(VineFlagOffset);
    if (!z)
        goto NextVO;
    writeData(VineStart_Y_Position, a);
NextVO:
    a = x;
    writeData(VineObjOffset + y, a);
    ++M(VineFlagOffset);
    a = Sfx_GrowVine;
    writeData(Square2SoundQueue, a);
    goto Return;

//---------------------------------------------------------------------

VineObjectHandler:
    compare(x, 0x05);
    if (!z)
        goto ExitVH;
    y = M(VineFlagOffset);
    --y;
    a = M(VineHeight);
    compare(a, M(VineHeightData + y));
    if (z)
        goto RunVSubs;
    a = M(FrameCounter);
    a >>= 1;
    a >>= 1;
    if (!c)
        goto RunVSubs;
    a = M(Enemy_Y_Position + 5);
    a -= 0x01;
    writeData(Enemy_Y_Position + 5, a);
    ++M(VineHeight);
RunVSubs:
    a = M(VineHeight);
    compare(a, 0x08);
    if (!c)
        goto ExitVH;
    JSR(RelativeEnemyPosition, 197)
    JSR(GetEnemyOffscreenBits, 198)
    y = 0x00;
VDrawLoop:
    JSR(DrawVine, 199)
    ++y;
    compare(y, M(VineFlagOffset));
    if (!z)
        goto VDrawLoop;
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001100);
    if (z)
        goto WrCMTile;
    --y;
KillVine:
    x = M(VineObjOffset + y);
    JSR(EraseEnemyObject, 200)
    --y;
    if (!n)
        goto KillVine;
    writeData(VineFlagOffset, a);
    writeData(VineHeight, a);
WrCMTile:
    a = M(VineHeight);
    compare(a, 0x20);
    if (!c)
        goto ExitVH;
    x = 0x06;
    a = 0x01;
    y = 0x1b;
    JSR(BlockBufferCollision, 201)
    y = M(0x02);
    compare(y, 0xd0);
    if (c)
        goto ExitVH;
    a = M(W(0x06) + y);
    if (!z)
        goto ExitVH;
    a = 0x26;
    writeData(W(0x06) + y, a);
ExitVH:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ProcessCannons:
    a = M(AreaType);
    if (z)
        goto ExCannon;
    x = 0x02;
ThreeSChk:
    writeData(ObjectOffset, x);
    a = M(Enemy_Flag + x);
    if (!z)
        goto Chk_BB;
    a = M(PseudoRandomBitReg + 1 + x);
    y = M(SecondaryHardMode);
    a &= M(CannonBitmasks + y);
    compare(a, 0x06);
    if (c)
        goto Chk_BB;
    y = a;
    a = M(Cannon_PageLoc + y);
    if (z)
        goto Chk_BB;
    a = M(Cannon_Timer + y);
    if (z)
        goto FireCannon;
    a -= 0x00;
    writeData(Cannon_Timer + y, a);
    goto Chk_BB;
FireCannon:
    a = M(TimerControl);
    if (!z)
        goto Chk_BB;
    a = 0x0e;
    writeData(Cannon_Timer + y, a);
    a = M(Cannon_PageLoc + y);
    writeData(Enemy_PageLoc + x, a);
    a = M(Cannon_X_Position + y);
    writeData(Enemy_X_Position + x, a);
    a = M(Cannon_Y_Position + y);
    c = 1;
    a -= 0x08;
    writeData(Enemy_Y_Position + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    a >>= 1;
    writeData(Enemy_State + x, a);
    a = 0x09;
    writeData(Enemy_BoundBoxCtrl + x, a);
    a = BulletBill_CannonVar;
    writeData(Enemy_ID + x, a);
    goto Next3Slt;
Chk_BB:
    a = M(Enemy_ID + x);
    compare(a, BulletBill_CannonVar);
    if (!z)
        goto Next3Slt;
    JSR(OffscreenBoundsCheck, 202)
    a = M(Enemy_Flag + x);
    if (z)
        goto Next3Slt;
    JSR(GetEnemyOffscreenBits, 203)
    JSR(BulletBillHandler, 204)
Next3Slt:
    --x;
    if (!n)
        goto ThreeSChk;
ExCannon:
    goto Return;

//---------------------------------------------------------------------

BulletBillHandler:
    a = M(TimerControl);
    if (!z)
        goto RunBBSubs;
    a = M(Enemy_State + x);
    if (!z)
        goto ChkDSte;
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001100);
    compare(a, BOOST_BINARY(00001100));
    if (z)
        goto KillBB;
    y = 0x01;
    JSR(PlayerEnemyDiff, 205)
    if (n)
        goto SetupBB;
    ++y;
SetupBB:
    writeData(Enemy_MovingDir + x, y);
    --y;
    a = M(BulletBillXSpdData + y);
    writeData(Enemy_X_Speed + x, a);
    a = M(0x00);
    a += 0x28;
    compare(a, 0x50);
    if (!c)
        goto KillBB;
    a = 0x01;
    writeData(Enemy_State + x, a);
    a = 0x0a;
    writeData(EnemyFrameTimer + x, a);
    a = Sfx_Blast;
    writeData(Square2SoundQueue, a);
ChkDSte:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto BBFly;
    JSR(MoveD_EnemyVertically, 206)
BBFly:
    JSR(MoveEnemyHorizontally, 207)
RunBBSubs:
    JSR(GetEnemyOffscreenBits, 208)
    JSR(RelativeEnemyPosition, 209)
    JSR(GetEnemyBoundBox, 210)
    JSR(PlayerEnemyCollision, 211)
    goto EnemyGfxHandler;
KillBB:
    JSR(EraseEnemyObject, 212)
    goto Return;

//---------------------------------------------------------------------

SpawnHammerObj:
    a = M(PseudoRandomBitReg + 1);
    a &= BOOST_BINARY(00000111);
    if (!z)
        goto SetMOfs;
    a = M(PseudoRandomBitReg + 1);
    a &= BOOST_BINARY(00001000);
SetMOfs:
    y = a;
    a = M(Misc_State + y);
    if (!z)
        goto NoHammer;
    x = M(HammerEnemyOfsData + y);
    a = M(Enemy_Flag + x);
    if (!z)
        goto NoHammer;
    x = M(ObjectOffset);
    a = x;
    writeData(HammerEnemyOffset + y, a);
    a = 0x90;
    writeData(Misc_State + y, a);
    a = 0x07;
    writeData(Misc_BoundBoxCtrl + y, a);
    c = 1;
    goto Return;

//---------------------------------------------------------------------

NoHammer:
    x = M(ObjectOffset);
    c = 0;
    goto Return;

//---------------------------------------------------------------------

ProcHammerObj:
    a = M(TimerControl);
    if (!z)
        goto RunHSubs;
    a = M(Misc_State + x);
    a &= BOOST_BINARY(01111111);
    y = M(HammerEnemyOffset + x);
    compare(a, 0x02);
    if (z)
        goto SetHSpd;
    if (c)
        goto SetHPos;
    a = x;
    c = 0;
    a += 0x0d;
    x = a;
    a = 0x10;
    writeData(0x00, a);
    a = 0x0f;
    writeData(0x01, a);
    a = 0x04;
    writeData(0x02, a);
    a = 0x00;
    JSR(ImposeGravity, 213)
    JSR(MoveObjectHorizontally, 214)
    x = M(ObjectOffset);
    goto RunAllH;
SetHSpd:
    a = 0xfe;
    writeData(Misc_Y_Speed + x, a);
    a = M(Enemy_State + y);
    a &= BOOST_BINARY(11110111);
    writeData(Enemy_State + y, a);
    x = M(Enemy_MovingDir + y);
    --x;
    a = M(HammerXSpdData + x);
    x = M(ObjectOffset);
    writeData(Misc_X_Speed + x, a);
SetHPos:
    --M(Misc_State + x);
    a = M(Enemy_X_Position + y);
    c = 0;
    a += 0x02;
    writeData(Misc_X_Position + x, a);
    a = M(Enemy_PageLoc + y);
    a += 0x00;
    writeData(Misc_PageLoc + x, a);
    a = M(Enemy_Y_Position + y);
    c = 1;
    a -= 0x0a;
    writeData(Misc_Y_Position + x, a);
    a = 0x01;
    writeData(Misc_Y_HighPos + x, a);
    if (!z)
        goto RunHSubs;
RunAllH:
    JSR(PlayerHammerCollision, 215)
RunHSubs:
    JSR(GetMiscOffscreenBits, 216)
    JSR(RelativeMiscPosition, 217)
    JSR(GetMiscBoundBox, 218)
    JSR(DrawHammer, 219)
    goto Return;

//---------------------------------------------------------------------

CoinBlock:
    JSR(FindEmptyMiscSlot, 220)
    a = M(Block_PageLoc + x);
    writeData(Misc_PageLoc + y, a);
    a = M(Block_X_Position + x);
    a |= 0x05;
    writeData(Misc_X_Position + y, a);
    a = M(Block_Y_Position + x);
    a -= 0x10;
    writeData(Misc_Y_Position + y, a);
    goto JCoinC;
SetupJumpCoin:
    JSR(FindEmptyMiscSlot, 221)
    a = M(Block_PageLoc2 + x);
    writeData(Misc_PageLoc + y, a);
    a = M(0x06);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a |= 0x05;
    writeData(Misc_X_Position + y, a);
    a = M(0x02);
    a += 0x20;
    writeData(Misc_Y_Position + y, a);
JCoinC:
    a = 0xfb;
    writeData(Misc_Y_Speed + y, a);
    a = 0x01;
    writeData(Misc_Y_HighPos + y, a);
    writeData(Misc_State + y, a);
    writeData(Square2SoundQueue, a);
    writeData(ObjectOffset, x);
    JSR(GiveOneCoin, 222)
    ++M(CoinTallyFor1Ups);
    goto Return;

//---------------------------------------------------------------------

FindEmptyMiscSlot:
    y = 0x08;
FMiscLoop:
    a = M(Misc_State + y);
    if (z)
        goto UseMiscS;
    --y;
    compare(y, 0x05);
    if (!z)
        goto FMiscLoop;
    y = 0x08;
UseMiscS:
    writeData(JumpCoinMiscOffset, y);
    goto Return;

//---------------------------------------------------------------------

MiscObjectsCore:
    x = 0x08;
MiscLoop:
    writeData(ObjectOffset, x);
    a = M(Misc_State + x);
    if (z)
        goto MiscLoopBack;
    a <<= 1;
    if (!c)
        goto ProcJumpCoin;
    JSR(ProcHammerObj, 223)
    goto MiscLoopBack;
ProcJumpCoin:
    y = M(Misc_State + x);
    --y;
    if (z)
        goto JCoinRun;
    ++M(Misc_State + x);
    a = M(Misc_X_Position + x);
    c = 0;
    a += M(ScrollAmount);
    writeData(Misc_X_Position + x, a);
    a = M(Misc_PageLoc + x);
    a += 0x00;
    writeData(Misc_PageLoc + x, a);
    a = M(Misc_State + x);
    compare(a, 0x30);
    if (!z)
        goto RunJCSubs;
    a = 0x00;
    writeData(Misc_State + x, a);
    goto MiscLoopBack;
JCoinRun:
    a = x;
    c = 0;
    a += 0x0d;
    x = a;
    a = 0x50;
    writeData(0x00, a);
    a = 0x06;
    writeData(0x02, a);
    a >>= 1;
    writeData(0x01, a);
    a = 0x00;
    JSR(ImposeGravity, 224)
    x = M(ObjectOffset);
    a = M(Misc_Y_Speed + x);
    compare(a, 0x05);
    if (!z)
        goto RunJCSubs;
    ++M(Misc_State + x);
RunJCSubs:
    JSR(RelativeMiscPosition, 225)
    JSR(GetMiscOffscreenBits, 226)
    JSR(GetMiscBoundBox, 227)
    JSR(JCoinGfxHandler, 228)
MiscLoopBack:
    --x;
    if (!n)
        goto MiscLoop;
    goto Return;

//---------------------------------------------------------------------

GiveOneCoin:
    a = 0x01;
    writeData(DigitModifier + 5, a);
    x = M(CurrentPlayer);
    y = M(CoinTallyOffsets + x);
    JSR(DigitsMathRoutine, 229)
    ++M(CoinTally);
    a = M(CoinTally);
    compare(a, 100);
    if (!z)
        goto CoinPoints;
    a = 0x00;
    writeData(CoinTally, a);
    ++M(NumberofLives);
    a = Sfx_ExtraLife;
    writeData(Square2SoundQueue, a);
CoinPoints:
    a = 0x02;
    writeData(DigitModifier + 4, a);
AddToScore:
    x = M(CurrentPlayer);
    y = M(ScoreOffsets + x);
    JSR(DigitsMathRoutine, 230)
GetSBNybbles:
    y = M(CurrentPlayer);
    a = M(StatusBarNybbles + y);
UpdateNumber:
    JSR(PrintStatusBarNumbers, 231)
    y = M(VRAM_Buffer1_Offset);
    a = M(VRAM_Buffer1 - 6 + y);
    if (!z)
        goto NoZSup;
    a = 0x24;
    writeData(VRAM_Buffer1 - 6 + y, a);
NoZSup:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

SetupPowerUp:
    a = PowerUpObject;
    writeData(Enemy_ID + 5, a);
    a = M(Block_PageLoc + x);
    writeData(Enemy_PageLoc + 5, a);
    a = M(Block_X_Position + x);
    writeData(Enemy_X_Position + 5, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + 5, a);
    a = M(Block_Y_Position + x);
    c = 1;
    a -= 0x08;
    writeData(Enemy_Y_Position + 5, a);
PwrUpJmp:
    a = 0x01;
    writeData(Enemy_State + 5, a);
    writeData(Enemy_Flag + 5, a);
    a = 0x03;
    writeData(Enemy_BoundBoxCtrl + 5, a);
    a = M(PowerUpType);
    compare(a, 0x02);
    if (c)
        goto PutBehind;
    a = M(PlayerStatus);
    compare(a, 0x02);
    if (!c)
        goto StrType;
    a >>= 1;
StrType:
    writeData(PowerUpType, a);
PutBehind:
    a = BOOST_BINARY(00100000);
    writeData(Enemy_SprAttrib + 5, a);
    a = Sfx_GrowPowerUp;
    writeData(Square2SoundQueue, a);
    goto Return;

//---------------------------------------------------------------------

PowerUpObjHandler:
    x = 0x05;
    writeData(ObjectOffset, x);
    a = M(Enemy_State + 5);
    if (z)
        goto ExitPUp;
    a <<= 1;
    if (!c)
        goto GrowThePowerUp;
    a = M(TimerControl);
    if (!z)
        goto RunPUSubs;
    a = M(PowerUpType);
    if (z)
        goto ShroomM;
    compare(a, 0x03);
    if (z)
        goto ShroomM;
    compare(a, 0x02);
    if (!z)
        goto RunPUSubs;
    JSR(MoveJumpingEnemy, 232)
    JSR(EnemyJump, 233)
    goto RunPUSubs;
ShroomM:
    JSR(MoveNormalEnemy, 234)
    JSR(EnemyToBGCollisionDet, 235)
    goto RunPUSubs;
GrowThePowerUp:
    a = M(FrameCounter);
    a &= 0x03;
    if (!z)
        goto ChkPUSte;
    --M(Enemy_Y_Position + 5);
    a = M(Enemy_State + 5);
    ++M(Enemy_State + 5);
    compare(a, 0x11);
    if (!c)
        goto ChkPUSte;
    a = 0x10;
    writeData(Enemy_X_Speed + x, a);
    a = BOOST_BINARY(10000000);
    writeData(Enemy_State + 5, a);
    a <<= 1;
    writeData(Enemy_SprAttrib + 5, a);
    a.rol();
    writeData(Enemy_MovingDir + x, a);
ChkPUSte:
    a = M(Enemy_State + 5);
    compare(a, 0x06);
    if (!c)
        goto ExitPUp;
RunPUSubs:
    JSR(RelativeEnemyPosition, 236)
    JSR(GetEnemyOffscreenBits, 237)
    JSR(GetEnemyBoundBox, 238)
    JSR(DrawPowerUp, 239)
    JSR(PlayerEnemyCollision, 240)
    JSR(OffscreenBoundsCheck, 241)
ExitPUp:
    goto Return;

//---------------------------------------------------------------------

PlayerHeadCollision:
    pha();
    a = 0x11;
    x = M(SprDataOffset_Ctrl);
    y = M(PlayerSize);
    if (!z)
        goto DBlockSte;
    a = 0x12;
DBlockSte:
    writeData(Block_State + x, a);
    JSR(DestroyBlockMetatile, 242)
    x = M(SprDataOffset_Ctrl);
    a = M(0x02);
    writeData(Block_Orig_YPos + x, a);
    y = a;
    a = M(0x06);
    writeData(Block_BBuf_Low + x, a);
    a = M(W(0x06) + y);
    JSR(BlockBumpedChk, 243)
    writeData(0x00, a);
    y = M(PlayerSize);
    if (!z)
        goto ChkBrick;
    a = y;
ChkBrick:
    if (!c)
        goto PutMTileB;
    y = 0x11;
    writeData(Block_State + x, y);
    a = 0xc4;
    y = M(0x00);
    compare(y, 0x58);
    if (z)
        goto StartBTmr;
    compare(y, 0x5d);
    if (!z)
        goto PutMTileB;
StartBTmr:
    a = M(BrickCoinTimerFlag);
    if (!z)
        goto ContBTmr;
    a = 0x0b;
    writeData(BrickCoinTimer, a);
    ++M(BrickCoinTimerFlag);
ContBTmr:
    a = M(BrickCoinTimer);
    if (!z)
        goto PutOldMT;
    y = 0xc4;
PutOldMT:
    a = y;
PutMTileB:
    writeData(Block_Metatile + x, a);
    JSR(InitBlock_XY_Pos, 244)
    y = M(0x02);
    a = 0x23;
    writeData(W(0x06) + y, a);
    a = 0x10;
    writeData(BlockBounceTimer, a);
    pla();
    writeData(0x05, a);
    y = 0x00;
    a = M(CrouchingFlag);
    if (!z)
        goto SmallBP;
    a = M(PlayerSize);
    if (z)
        goto BigBP;
SmallBP:
    ++y;
BigBP:
    a = M(Player_Y_Position);
    c = 0;
    a += M(BlockYPosAdderData + y);
    a &= 0xf0;
    writeData(Block_Y_Position + x, a);
    y = M(Block_State + x);
    compare(y, 0x11);
    if (z)
        goto Unbreak;
    JSR(BrickShatter, 245)
    goto InvOBit;
Unbreak:
    JSR(BumpBlock, 246)
InvOBit:
    a = M(SprDataOffset_Ctrl);
    a ^= 0x01;
    writeData(SprDataOffset_Ctrl, a);
    goto Return;

//---------------------------------------------------------------------

InitBlock_XY_Pos:
    a = M(Player_X_Position);
    c = 0;
    a += 0x08;
    a &= 0xf0;
    writeData(Block_X_Position + x, a);
    a = M(Player_PageLoc);
    a += 0x00;
    writeData(Block_PageLoc + x, a);
    writeData(Block_PageLoc2 + x, a);
    a = M(Player_Y_HighPos);
    writeData(Block_Y_HighPos + x, a);
    goto Return;

//---------------------------------------------------------------------

BumpBlock:
    JSR(CheckTopOfBlock, 247)
    a = Sfx_Bump;
    writeData(Square1SoundQueue, a);
    a = 0x00;
    writeData(Block_X_Speed + x, a);
    writeData(Block_Y_MoveForce + x, a);
    writeData(Player_Y_Speed, a);
    a = 0xfe;
    writeData(Block_Y_Speed + x, a);
    a = M(0x05);
    JSR(BlockBumpedChk, 248)
    if (!c)
        goto ExitBlockChk;
    a = y;
    compare(a, 0x09);
    if (!c)
        goto BlockCode;
    a -= 0x05;
BlockCode:
    switch(a)
        {
    case 0:
        goto MushFlowerBlock;
    case 1:
        goto CoinBlock;
    case 2:
        goto CoinBlock;
    case 3:
        goto ExtraLifeMushBlock;
    case 4:
        goto MushFlowerBlock;
    case 5:
        goto VineBlock;
    case 6:
        goto StarBlock;
    case 7:
        goto CoinBlock;
    case 8:
        goto ExtraLifeMushBlock;
    }
MushFlowerBlock:
    a = 0x00;
    goto Skip_4;
StarBlock:
    a = 0x02;
Skip_4:
    goto Skip_5;
ExtraLifeMushBlock:
    a = 0x03;
Skip_5:
    writeData(0x39, a);
    goto SetupPowerUp;
VineBlock:
    x = 0x05;
    y = M(SprDataOffset_Ctrl);
    JSR(Setup_Vine, 249)
ExitBlockChk:
    goto Return;

//---------------------------------------------------------------------

BlockBumpedChk:
    y = 0x0d;
BumpChkLoop:
    compare(a, M(BrickQBlockMetatiles + y));
    if (z)
        goto MatchBump;
    --y;
    if (!n)
        goto BumpChkLoop;
    c = 0;
MatchBump:
    goto Return;

//---------------------------------------------------------------------

BrickShatter:
    JSR(CheckTopOfBlock, 250)
    a = Sfx_BrickShatter;
    writeData(Block_RepFlag + x, a);
    writeData(NoiseSoundQueue, a);
    JSR(SpawnBrickChunks, 251)
    a = 0xfe;
    writeData(Player_Y_Speed, a);
    a = 0x05;
    writeData(DigitModifier + 5, a);
    JSR(AddToScore, 252)
    x = M(SprDataOffset_Ctrl);
    goto Return;

//---------------------------------------------------------------------

CheckTopOfBlock:
    x = M(SprDataOffset_Ctrl);
    y = M(0x02);
    if (z)
        goto TopEx;
    a = y;
    c = 1;
    a -= 0x10;
    writeData(0x02, a);
    y = a;
    a = M(W(0x06) + y);
    compare(a, 0xc2);
    if (!z)
        goto TopEx;
    a = 0x00;
    writeData(W(0x06) + y, a);
    JSR(RemoveCoin_Axe, 253)
    x = M(SprDataOffset_Ctrl);
    JSR(SetupJumpCoin, 254)
TopEx:
    goto Return;

//---------------------------------------------------------------------

SpawnBrickChunks:
    a = M(Block_X_Position + x);
    writeData(Block_Orig_XPos + x, a);
    a = 0xf0;
    writeData(Block_X_Speed + x, a);
    writeData(Block_X_Speed + 2 + x, a);
    a = 0xfa;
    writeData(Block_Y_Speed + x, a);
    a = 0xfc;
    writeData(Block_Y_Speed + 2 + x, a);
    a = 0x00;
    writeData(Block_Y_MoveForce + x, a);
    writeData(Block_Y_MoveForce + 2 + x, a);
    a = M(Block_PageLoc + x);
    writeData(Block_PageLoc + 2 + x, a);
    a = M(Block_X_Position + x);
    writeData(Block_X_Position + 2 + x, a);
    a = M(Block_Y_Position + x);
    c = 0;
    a += 0x08;
    writeData(Block_Y_Position + 2 + x, a);
    a = 0xfa;
    writeData(Block_Y_Speed + x, a);
    goto Return;

//---------------------------------------------------------------------

BlockObjectsCore:
    a = M(Block_State + x);
    if (z)
        goto UpdSte;
    a &= 0x0f;
    pha();
    y = a;
    a = x;
    c = 0;
    a += 0x09;
    x = a;
    --y;
    if (z)
        goto BouncingBlockHandler;
    JSR(ImposeGravityBlock, 255)
    JSR(MoveObjectHorizontally, 256)
    a = x;
    c = 0;
    a += 0x02;
    x = a;
    JSR(ImposeGravityBlock, 257)
    JSR(MoveObjectHorizontally, 258)
    x = M(ObjectOffset);
    JSR(RelativeBlockPosition, 259)
    JSR(GetBlockOffscreenBits, 260)
    JSR(DrawBrickChunks, 261)
    pla();
    y = M(Block_Y_HighPos + x);
    if (z)
        goto UpdSte;
    pha();
    a = 0xf0;
    compare(a, M(Block_Y_Position + 2 + x));
    if (c)
        goto ChkTop;
    writeData(Block_Y_Position + 2 + x, a);
ChkTop:
    a = M(Block_Y_Position + x);
    compare(a, 0xf0);
    pla();
    if (!c)
        goto UpdSte;
    if (c)
        goto KillBlock;
BouncingBlockHandler:
    JSR(ImposeGravityBlock, 262)
    x = M(ObjectOffset);
    JSR(RelativeBlockPosition, 263)
    JSR(GetBlockOffscreenBits, 264)
    JSR(DrawBlock, 265)
    a = M(Block_Y_Position + x);
    a &= 0x0f;
    compare(a, 0x05);
    pla();
    if (c)
        goto UpdSte;
    a = 0x01;
    writeData(Block_RepFlag + x, a);
KillBlock:
    a = 0x00;
UpdSte:
    writeData(Block_State + x, a);
    goto Return;

//---------------------------------------------------------------------

BlockObjMT_Updater:
    x = 0x01;
UpdateLoop:
    writeData(ObjectOffset, x);
    a = M(VRAM_Buffer1);
    if (!z)
        goto NextBUpd;
    a = M(Block_RepFlag + x);
    if (z)
        goto NextBUpd;
    a = M(Block_BBuf_Low + x);
    writeData(0x06, a);
    a = 0x05;
    writeData(0x07, a);
    a = M(Block_Orig_YPos + x);
    writeData(0x02, a);
    y = a;
    a = M(Block_Metatile + x);
    writeData(W(0x06) + y, a);
    JSR(ReplaceBlockMetatile, 266)
    a = 0x00;
    writeData(Block_RepFlag + x, a);
NextBUpd:
    --x;
    if (!n)
        goto UpdateLoop;
    goto Return;

//---------------------------------------------------------------------

MoveEnemyHorizontally:
    ++x;
    JSR(MoveObjectHorizontally, 267)
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

MovePlayerHorizontally:
    a = M(JumpspringAnimCtrl);
    if (!z)
        goto ExXMove;
    x = a;
MoveObjectHorizontally:
    a = M(SprObject_X_Speed + x);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    writeData(0x01, a);
    a = M(SprObject_X_Speed + x);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    compare(a, 0x08);
    if (!c)
        goto SaveXSpd;
    a |= BOOST_BINARY(11110000);
SaveXSpd:
    writeData(0x00, a);
    y = 0x00;
    compare(a, 0x00);
    if (!n)
        goto UseAdder;
    --y;
UseAdder:
    writeData(0x02, y);
    a = M(SprObject_X_MoveForce + x);
    c = 0;
    a += M(0x01);
    writeData(SprObject_X_MoveForce + x, a);
    a = 0x00;
    a.rol();
    pha();
    a.ror();
    a = M(SprObject_X_Position + x);
    a += M(0x00);
    writeData(SprObject_X_Position + x, a);
    a = M(SprObject_PageLoc + x);
    a += M(0x02);
    writeData(SprObject_PageLoc + x, a);
    pla();
    c = 0;
    a += M(0x00);
ExXMove:
    goto Return;

//---------------------------------------------------------------------

MovePlayerVertically:
    x = 0x00;
    a = M(TimerControl);
    if (!z)
        goto NoJSChk;
    a = M(JumpspringAnimCtrl);
    if (!z)
        goto ExXMove;
NoJSChk:
    a = M(VerticalForce);
    writeData(0x00, a);
    a = 0x04;
    goto ImposeGravitySprObj;
MoveD_EnemyVertically:
    y = 0x3d;
    a = M(Enemy_State + x);
    compare(a, 0x05);
    if (!z)
        goto ContVMove;
MoveFallingPlatform:
    y = 0x20;
ContVMove:
    goto SetHiMax;
MoveRedPTroopaDown:
    y = 0x00;
    goto MoveRedPTroopa;
MoveRedPTroopaUp:
    y = 0x01;
MoveRedPTroopa:
    ++x;
    a = 0x03;
    writeData(0x00, a);
    a = 0x06;
    writeData(0x01, a);
    a = 0x02;
    writeData(0x02, a);
    a = y;
    goto RedPTroopaGrav;
MoveDropPlatform:
    y = 0x7f;
    if (!z)
        goto SetMdMax;
MoveEnemySlowVert:
    y = 0x0f;
SetMdMax:
    a = 0x02;
    if (!z)
        goto SetXMoveAmt;
MoveJ_EnemyVertically:
    y = 0x1c;
SetHiMax:
    a = 0x03;
SetXMoveAmt:
    writeData(0x00, y);
    ++x;
    JSR(ImposeGravitySprObj, 268)
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ResidualGravityCode:
    y = 0x00;
    goto Skip_6;
ImposeGravityBlock:
    y = 0x01;
Skip_6:
    a = 0x50;
    writeData(0x00, a);
    a = M(MaxSpdBlockData + y);
ImposeGravitySprObj:
    writeData(0x02, a);
    a = 0x00;
    goto ImposeGravity;
MovePlatformDown:
    a = 0x00;
    goto Skip_7;
MovePlatformUp:
    a = 0x01;
Skip_7:
    pha();
    y = M(Enemy_ID + x);
    ++x;
    a = 0x05;
    compare(y, 0x29);
    if (!z)
        goto SetDplSpd;
    a = 0x09;
SetDplSpd:
    writeData(0x00, a);
    a = 0x0a;
    writeData(0x01, a);
    a = 0x03;
    writeData(0x02, a);
    pla();
    y = a;
RedPTroopaGrav:
    JSR(ImposeGravity, 269)
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ImposeGravity:
    pha();
    a = M(SprObject_YMF_Dummy + x);
    c = 0;
    a += M(SprObject_Y_MoveForce + x);
    writeData(SprObject_YMF_Dummy + x, a);
    y = 0x00;
    a = M(SprObject_Y_Speed + x);
    if (!n)
        goto AlterYP;
    --y;
AlterYP:
    writeData(0x07, y);
    a += M(SprObject_Y_Position + x);
    writeData(SprObject_Y_Position + x, a);
    a = M(SprObject_Y_HighPos + x);
    a += M(0x07);
    writeData(SprObject_Y_HighPos + x, a);
    a = M(SprObject_Y_MoveForce + x);
    c = 0;
    a += M(0x00);
    writeData(SprObject_Y_MoveForce + x, a);
    a = M(SprObject_Y_Speed + x);
    a += 0x00;
    writeData(SprObject_Y_Speed + x, a);
    compare(a, M(0x02));
    if (n)
        goto ChkUpM;
    a = M(SprObject_Y_MoveForce + x);
    compare(a, 0x80);
    if (!c)
        goto ChkUpM;
    a = M(0x02);
    writeData(SprObject_Y_Speed + x, a);
    a = 0x00;
    writeData(SprObject_Y_MoveForce + x, a);
ChkUpM:
    pla();
    if (z)
        goto ExVMove;
    a = M(0x02);
    a ^= BOOST_BINARY(11111111);
    y = a;
    ++y;
    writeData(0x07, y);
    a = M(SprObject_Y_MoveForce + x);
    c = 1;
    a -= M(0x01);
    writeData(SprObject_Y_MoveForce + x, a);
    a = M(SprObject_Y_Speed + x);
    a -= 0x00;
    writeData(SprObject_Y_Speed + x, a);
    compare(a, M(0x07));
    if (!n)
        goto ExVMove;
    a = M(SprObject_Y_MoveForce + x);
    compare(a, 0x80);
    if (c)
        goto ExVMove;
    a = M(0x07);
    writeData(SprObject_Y_Speed + x, a);
    a = 0xff;
    writeData(SprObject_Y_MoveForce + x, a);
ExVMove:
    goto Return;

//---------------------------------------------------------------------

EnemiesAndLoopsCore:
    a = M(Enemy_Flag + x);
    pha();
    a <<= 1;
    if (c)
        goto ChkBowserF;
    pla();
    if (z)
        goto ChkAreaTsk;
    goto RunEnemyObjectsCore;
ChkAreaTsk:
    a = M(AreaParserTaskNum);
    a &= 0x07;
    compare(a, 0x07);
    if (z)
        goto ExitELCore;
    goto ProcLoopCommand;
ChkBowserF:
    pla();
    a &= BOOST_BINARY(00001111);
    y = a;
    a = M(Enemy_Flag + y);
    if (!z)
        goto ExitELCore;
    writeData(Enemy_Flag + x, a);
ExitELCore:
    goto Return;

//---------------------------------------------------------------------

ExecGameLoopback:
    a = M(Player_PageLoc);
    c = 1;
    a -= 0x04;
    writeData(Player_PageLoc, a);
    a = M(CurrentPageLoc);
    c = 1;
    a -= 0x04;
    writeData(CurrentPageLoc, a);
    a = M(ScreenLeft_PageLoc);
    c = 1;
    a -= 0x04;
    writeData(ScreenLeft_PageLoc, a);
    a = M(ScreenRight_PageLoc);
    c = 1;
    a -= 0x04;
    writeData(ScreenRight_PageLoc, a);
    a = M(AreaObjectPageLoc);
    c = 1;
    a -= 0x04;
    writeData(AreaObjectPageLoc, a);
    a = 0x00;
    writeData(EnemyObjectPageSel, a);
    writeData(AreaObjectPageSel, a);
    writeData(EnemyDataOffset, a);
    writeData(EnemyObjectPageLoc, a);
    a = M(AreaDataOfsLoopback + y);
    writeData(AreaDataOffset, a);
    goto Return;

//---------------------------------------------------------------------

ProcLoopCommand:
    a = M(LoopCommand);
    if (z)
        goto ChkEnemyFrenzy;
    a = M(CurrentColumnPos);
    if (!z)
        goto ChkEnemyFrenzy;
    y = 0x0b;
FindLoop:
    --y;
    if (n)
        goto ChkEnemyFrenzy;
    a = M(WorldNumber);
    compare(a, M(LoopCmdWorldNumber + y));
    if (!z)
        goto FindLoop;
    a = M(CurrentPageLoc);
    compare(a, M(LoopCmdPageNumber + y));
    if (!z)
        goto FindLoop;
    a = M(Player_Y_Position);
    compare(a, M(LoopCmdYPosition + y));
    if (!z)
        goto WrongChk;
    a = M(Player_State);
    compare(a, 0x00);
    if (!z)
        goto WrongChk;
    a = M(WorldNumber);
    compare(a, World7);
    if (!z)
        goto InitMLp;
    ++M(MultiLoopCorrectCntr);
IncMLoop:
    ++M(MultiLoopPassCntr);
    a = M(MultiLoopPassCntr);
    compare(a, 0x03);
    if (!z)
        goto InitLCmd;
    a = M(MultiLoopCorrectCntr);
    compare(a, 0x03);
    if (z)
        goto InitMLp;
    if (!z)
        goto DoLpBack;
WrongChk:
    a = M(WorldNumber);
    compare(a, World7);
    if (z)
        goto IncMLoop;
DoLpBack:
    JSR(ExecGameLoopback, 270)
    JSR(KillAllEnemies, 271)
InitMLp:
    a = 0x00;
    writeData(MultiLoopPassCntr, a);
    writeData(MultiLoopCorrectCntr, a);
InitLCmd:
    a = 0x00;
    writeData(LoopCommand, a);
ChkEnemyFrenzy:
    a = M(EnemyFrenzyQueue);
    if (z)
        goto ProcessEnemyData;
    writeData(Enemy_ID + x, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    a = 0x00;
    writeData(Enemy_State + x, a);
    writeData(EnemyFrenzyQueue, a);
    goto InitEnemyObject;
ProcessEnemyData:
    y = M(EnemyDataOffset);
    a = M(W(EnemyData) + y);
    compare(a, 0xff);
    if (!z)
        goto CheckEndofBuffer;
    goto CheckFrenzyBuffer;
CheckEndofBuffer:
    a &= BOOST_BINARY(00001111);
    compare(a, 0x0e);
    if (z)
        goto CheckRightBounds;
    compare(x, 0x05);
    if (!c)
        goto CheckRightBounds;
    ++y;
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00111111);
    compare(a, 0x2e);
    if (z)
        goto CheckRightBounds;
    goto Return;

//---------------------------------------------------------------------

CheckRightBounds:
    a = M(ScreenRight_X_Pos);
    c = 0;
    a += 0x30;
    a &= BOOST_BINARY(11110000);
    writeData(0x07, a);
    a = M(ScreenRight_PageLoc);
    a += 0x00;
    writeData(0x06, a);
    y = M(EnemyDataOffset);
    ++y;
    a = M(W(EnemyData) + y);
    a <<= 1;
    if (!c)
        goto CheckPageCtrlRow;
    a = M(EnemyObjectPageSel);
    if (!z)
        goto CheckPageCtrlRow;
    ++M(EnemyObjectPageSel);
    ++M(EnemyObjectPageLoc);
CheckPageCtrlRow:
    --y;
    a = M(W(EnemyData) + y);
    a &= 0x0f;
    compare(a, 0x0f);
    if (!z)
        goto PositionEnemyObj;
    a = M(EnemyObjectPageSel);
    if (!z)
        goto PositionEnemyObj;
    ++y;
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00111111);
    writeData(EnemyObjectPageLoc, a);
    ++M(EnemyDataOffset);
    ++M(EnemyDataOffset);
    ++M(EnemyObjectPageSel);
    goto ProcLoopCommand;
PositionEnemyObj:
    a = M(EnemyObjectPageLoc);
    writeData(Enemy_PageLoc + x, a);
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(11110000);
    writeData(Enemy_X_Position + x, a);
    compare(a, M(ScreenRight_X_Pos));
    a = M(Enemy_PageLoc + x);
    a -= M(ScreenRight_PageLoc);
    if (c)
        goto CheckRightExtBounds;
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00001111);
    compare(a, 0x0e);
    if (z)
        goto ParseRow0e;
    goto CheckThreeBytes;
CheckRightExtBounds:
    a = M(0x07);
    compare(a, M(Enemy_X_Position + x));
    a = M(0x06);
    a -= M(Enemy_PageLoc + x);
    if (!c)
        goto CheckFrenzyBuffer;
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    a = M(W(EnemyData) + y);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    writeData(Enemy_Y_Position + x, a);
    compare(a, 0xe0);
    if (z)
        goto ParseRow0e;
    ++y;
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(01000000);
    if (z)
        goto CheckForEnemyGroup;
    a = M(SecondaryHardMode);
    if (z)
        goto Inc2B;
CheckForEnemyGroup:
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00111111);
    compare(a, 0x37);
    if (!c)
        goto BuzzyBeetleMutate;
    compare(a, 0x3f);
    if (!c)
        goto DoGroup;
BuzzyBeetleMutate:
    compare(a, Goomba);
    if (!z)
        goto StrID;
    y = M(PrimaryHardMode);
    if (z)
        goto StrID;
    a = BuzzyBeetle;
StrID:
    writeData(Enemy_ID + x, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    JSR(InitEnemyObject, 272)
    a = M(Enemy_Flag + x);
    if (!z)
        goto Inc2B;
    goto Return;

//---------------------------------------------------------------------

CheckFrenzyBuffer:
    a = M(EnemyFrenzyBuffer);
    if (!z)
        goto StrFre;
    a = M(VineFlagOffset);
    compare(a, 0x01);
    if (!z)
        goto ExEPar;
    a = VineObject;
StrFre:
    writeData(Enemy_ID + x, a);
InitEnemyObject:
    a = 0x00;
    writeData(Enemy_State + x, a);
    JSR(CheckpointEnemyID, 273)
ExEPar:
    goto Return;

//---------------------------------------------------------------------

DoGroup:
    goto HandleGroupEnemies;
ParseRow0e:
    ++y;
    ++y;
    a = M(W(EnemyData) + y);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    compare(a, M(WorldNumber));
    if (!z)
        goto NotUse;
    --y;
    a = M(W(EnemyData) + y);
    writeData(AreaPointer, a);
    ++y;
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00011111);
    writeData(EntrancePage, a);
NotUse:
    goto Inc3B;
CheckThreeBytes:
    y = M(EnemyDataOffset);
    a = M(W(EnemyData) + y);
    a &= BOOST_BINARY(00001111);
    compare(a, 0x0e);
    if (!z)
        goto Inc2B;
Inc3B:
    ++M(EnemyDataOffset);
Inc2B:
    ++M(EnemyDataOffset);
    ++M(EnemyDataOffset);
    a = 0x00;
    writeData(EnemyObjectPageSel, a);
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

CheckpointEnemyID:
    a = M(Enemy_ID + x);
    compare(a, 0x15);
    if (c)
        goto InitEnemyRoutines;
    y = a;
    a = M(Enemy_Y_Position + x);
    a += 0x08;
    writeData(Enemy_Y_Position + x, a);
    a = 0x01;
    writeData(EnemyOffscrBitsMasked + x, a);
    a = y;
InitEnemyRoutines:
    switch(a)
        {
    case 0:
        goto InitNormalEnemy;
    case 1:
        goto InitNormalEnemy;
    case 2:
        goto InitNormalEnemy;
    case 3:
        goto InitRedKoopa;
    case 4:
        goto NoInitCode;
    case 5:
        goto InitHammerBro;
    case 6:
        goto InitGoomba;
    case 7:
        goto InitBloober;
    case 8:
        goto InitBulletBill;
    case 9:
        goto NoInitCode;
    case 10:
        goto InitCheepCheep;
    case 11:
        goto InitCheepCheep;
    case 12:
        goto InitPodoboo;
    case 13:
        goto InitPiranhaPlant;
    case 14:
        goto InitJumpGPTroopa;
    case 15:
        goto InitRedPTroopa;
    case 16:
        goto InitHorizFlySwimEnemy;
    case 17:
        goto InitLakitu;
    case 18:
        goto InitEnemyFrenzy;
    case 19:
        goto NoInitCode;
    case 20:
        goto InitEnemyFrenzy;
    case 21:
        goto InitEnemyFrenzy;
    case 22:
        goto InitEnemyFrenzy;
    case 23:
        goto InitEnemyFrenzy;
    case 24:
        goto EndFrenzy;
    case 25:
        goto NoInitCode;
    case 26:
        goto NoInitCode;
    case 27:
        goto InitShortFirebar;
    case 28:
        goto InitShortFirebar;
    case 29:
        goto InitShortFirebar;
    case 30:
        goto InitShortFirebar;
    case 31:
        goto InitLongFirebar;
    case 32:
        goto NoInitCode;
    case 33:
        goto NoInitCode;
    case 34:
        goto NoInitCode;
    case 35:
        goto NoInitCode;
    case 36:
        goto InitBalPlatform;
    case 37:
        goto InitVertPlatform;
    case 38:
        goto LargeLiftUp;
    case 39:
        goto LargeLiftDown;
    case 40:
        goto InitHoriPlatform;
    case 41:
        goto InitDropPlatform;
    case 42:
        goto InitHoriPlatform;
    case 43:
        goto PlatLiftUp;
    case 44:
        goto PlatLiftDown;
    case 45:
        goto InitBowser;
    case 46:
        goto PwrUpJmp;
    case 47:
        goto Setup_Vine;
    case 48:
        goto NoInitCode;
    case 49:
        goto NoInitCode;
    case 50:
        goto NoInitCode;
    case 51:
        goto NoInitCode;
    case 52:
        goto NoInitCode;
    case 53:
        goto InitRetainerObj;
    case 54:
        goto EndOfEnemyInitCode;
    }
NoInitCode:
    goto Return;

//---------------------------------------------------------------------

InitGoomba:
    JSR(InitNormalEnemy, 274)
    goto SmallBBox;
InitPodoboo:
    a = 0x02;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Y_Position + x, a);
    a >>= 1;
    writeData(EnemyIntervalTimer + x, a);
    a >>= 1;
    writeData(Enemy_State + x, a);
    goto SmallBBox;
InitRetainerObj:
    a = 0xb8;
    writeData(Enemy_Y_Position + x, a);
    goto Return;

//---------------------------------------------------------------------

InitNormalEnemy:
    y = 0x01;
    a = M(PrimaryHardMode);
    if (!z)
        goto GetESpd;
    --y;
GetESpd:
    a = M(NormalXSpdData + y);
SetESpd:
    writeData(Enemy_X_Speed + x, a);
    goto TallBBox;
InitRedKoopa:
    JSR(InitNormalEnemy, 275)
    a = 0x01;
    writeData(Enemy_State + x, a);
    goto Return;

//---------------------------------------------------------------------

InitHammerBro:
    a = 0x00;
    writeData(HammerThrowingTimer + x, a);
    writeData(Enemy_X_Speed + x, a);
    y = M(SecondaryHardMode);
    a = M(HBroWalkingTimerData + y);
    writeData(EnemyIntervalTimer + x, a);
    a = 0x0b;
    goto SetBBox;
InitHorizFlySwimEnemy:
    a = 0x00;
    goto SetESpd;
InitBloober:
    a = 0x00;
    writeData(BlooperMoveSpeed + x, a);
SmallBBox:
    a = 0x09;
    if (!z)
        goto SetBBox;
InitRedPTroopa:
    y = 0x30;
    a = M(Enemy_Y_Position + x);
    writeData(RedPTroopaOrigXPos + x, a);
    if (!n)
        goto GetCent;
    y = 0xe0;
GetCent:
    a = y;
    a += M(Enemy_Y_Position + x);
    writeData(RedPTroopaCenterYPos + x, a);
TallBBox:
    a = 0x03;
SetBBox:
    writeData(Enemy_BoundBoxCtrl + x, a);
    a = 0x02;
    writeData(Enemy_MovingDir + x, a);
InitVStf:
    a = 0x00;
    writeData(Enemy_Y_Speed + x, a);
    writeData(Enemy_Y_MoveForce + x, a);
    goto Return;

//---------------------------------------------------------------------

InitBulletBill:
    a = 0x02;
    writeData(Enemy_MovingDir + x, a);
    a = 0x09;
    writeData(Enemy_BoundBoxCtrl + x, a);
    goto Return;

//---------------------------------------------------------------------

InitCheepCheep:
    JSR(SmallBBox, 276)
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00010000);
    writeData(CheepCheepMoveMFlag + x, a);
    a = M(Enemy_Y_Position + x);
    writeData(CheepCheepOrigYPos + x, a);
    goto Return;

//---------------------------------------------------------------------

InitLakitu:
    a = M(EnemyFrenzyBuffer);
    if (!z)
        goto KillLakitu;
SetupLakitu:
    a = 0x00;
    writeData(LakituReappearTimer, a);
    JSR(InitHorizFlySwimEnemy, 277)
    goto TallBBox2;
KillLakitu:
    goto EraseEnemyObject;
LakituAndSpinyHandler:
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto ExLSHand;
    compare(x, 0x05);
    if (c)
        goto ExLSHand;
    a = 0x80;
    writeData(FrenzyEnemyTimer, a);
    y = 0x04;
ChkLak:
    a = M(Enemy_ID + y);
    compare(a, Lakitu);
    if (z)
        goto CreateSpiny;
    --y;
    if (!n)
        goto ChkLak;
    ++M(LakituReappearTimer);
    a = M(LakituReappearTimer);
    compare(a, 0x07);
    if (!c)
        goto ExLSHand;
    x = 0x04;
ChkNoEn:
    a = M(Enemy_Flag + x);
    if (z)
        goto CreateL;
    --x;
    if (!n)
        goto ChkNoEn;
    if (n)
        goto RetEOfs;
CreateL:
    a = 0x00;
    writeData(Enemy_State + x, a);
    a = Lakitu;
    writeData(Enemy_ID + x, a);
    JSR(SetupLakitu, 278)
    a = 0x20;
    JSR(PutAtRightExtent, 279)
RetEOfs:
    x = M(ObjectOffset);
ExLSHand:
    goto Return;

//---------------------------------------------------------------------

CreateSpiny:
    a = M(Player_Y_Position);
    compare(a, 0x2c);
    if (!c)
        goto ExLSHand;
    a = M(Enemy_State + y);
    if (!z)
        goto ExLSHand;
    a = M(Enemy_PageLoc + y);
    writeData(Enemy_PageLoc + x, a);
    a = M(Enemy_X_Position + y);
    writeData(Enemy_X_Position + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    a = M(Enemy_Y_Position + y);
    c = 1;
    a -= 0x08;
    writeData(Enemy_Y_Position + x, a);
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    y = a;
    x = 0x02;
DifLoop:
    a = M(PRDiffAdjustData + y);
    writeData(0x01 + x, a);
    ++y;
    ++y;
    ++y;
    ++y;
    --x;
    if (!n)
        goto DifLoop;
    x = M(ObjectOffset);
    JSR(PlayerLakituDiff, 280)
    y = M(Player_X_Speed);
    compare(y, 0x08);
    if (c)
        goto SetSpSpd;
    y = a;
    a = M(PseudoRandomBitReg + 1 + x);
    a &= BOOST_BINARY(00000011);
    if (z)
        goto UsePosv;
    a = y;
    a ^= BOOST_BINARY(11111111);
    y = a;
    ++y;
UsePosv:
    a = y;
SetSpSpd:
    JSR(SmallBBox, 281)
    y = 0x02;
    writeData(Enemy_X_Speed + x, a);
    compare(a, 0x00);
    if (n)
        goto SpinyRte;
    --y;
SpinyRte:
    writeData(Enemy_MovingDir + x, y);
    a = 0xfd;
    writeData(Enemy_Y_Speed + x, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    a = 0x05;
    writeData(Enemy_State + x, a);
ChpChpEx:
    goto Return;

//---------------------------------------------------------------------

InitLongFirebar:
    JSR(DuplicateEnemyObj, 282)
InitShortFirebar:
    a = 0x00;
    writeData(FirebarSpinState_Low + x, a);
    a = M(Enemy_ID + x);
    c = 1;
    a -= 0x1b;
    y = a;
    a = M(FirebarSpinSpdData + y);
    writeData(FirebarSpinSpeed + x, a);
    a = M(FirebarSpinDirData + y);
    writeData(FirebarSpinDirection + x, a);
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += 0x04;
    writeData(Enemy_Y_Position + x, a);
    a = M(Enemy_X_Position + x);
    c = 0;
    a += 0x04;
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a += 0x00;
    writeData(Enemy_PageLoc + x, a);
    goto TallBBox2;
InitFlyingCheepCheep:
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto ChpChpEx;
    JSR(SmallBBox, 283)
    a = M(PseudoRandomBitReg + 1 + x);
    a &= BOOST_BINARY(00000011);
    y = a;
    a = M(FlyCCTimerData + y);
    writeData(FrenzyEnemyTimer, a);
    y = 0x03;
    a = M(SecondaryHardMode);
    if (z)
        goto MaxCC;
    ++y;
MaxCC:
    writeData(0x00, y);
    compare(x, M(0x00));
    if (c)
        goto ChpChpEx;
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    writeData(0x00, a);
    writeData(0x01, a);
    a = 0xfb;
    writeData(Enemy_Y_Speed + x, a);
    a = 0x00;
    y = M(Player_X_Speed);
    if (z)
        goto GSeed;
    a = 0x04;
    compare(y, 0x19);
    if (!c)
        goto GSeed;
    a <<= 1;
GSeed:
    pha();
    c = 0;
    a += M(0x00);
    writeData(0x00, a);
    a = M(PseudoRandomBitReg + 1 + x);
    a &= BOOST_BINARY(00000011);
    if (z)
        goto RSeed;
    a = M(PseudoRandomBitReg + 2 + x);
    a &= BOOST_BINARY(00001111);
    writeData(0x00, a);
RSeed:
    pla();
    c = 0;
    a += M(0x01);
    y = a;
    a = M(FlyCCXSpeedData + y);
    writeData(Enemy_X_Speed + x, a);
    a = 0x01;
    writeData(Enemy_MovingDir + x, a);
    a = M(Player_X_Speed);
    if (!z)
        goto D2XPos1;
    y = M(0x00);
    a = y;
    a &= BOOST_BINARY(00000010);
    if (z)
        goto D2XPos1;
    a = M(Enemy_X_Speed + x);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(Enemy_X_Speed + x, a);
    ++M(Enemy_MovingDir + x);
D2XPos1:
    a = y;
    a &= BOOST_BINARY(00000010);
    if (z)
        goto D2XPos2;
    a = M(Player_X_Position);
    c = 0;
    a += M(FlyCCXPositionData + y);
    writeData(Enemy_X_Position + x, a);
    a = M(Player_PageLoc);
    a += 0x00;
    goto FinCCSt;
D2XPos2:
    a = M(Player_X_Position);
    c = 1;
    a -= M(FlyCCXPositionData + y);
    writeData(Enemy_X_Position + x, a);
    a = M(Player_PageLoc);
    a -= 0x00;
FinCCSt:
    writeData(Enemy_PageLoc + x, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    writeData(Enemy_Y_HighPos + x, a);
    a = 0xf8;
    writeData(Enemy_Y_Position + x, a);
    goto Return;

//---------------------------------------------------------------------

InitBowser:
    JSR(DuplicateEnemyObj, 284)
    writeData(BowserFront_Offset, x);
    a = 0x00;
    writeData(BowserBodyControls, a);
    writeData(BridgeCollapseOffset, a);
    a = M(Enemy_X_Position + x);
    writeData(BowserOrigXPos, a);
    a = 0xdf;
    writeData(BowserFireBreathTimer, a);
    writeData(Enemy_MovingDir + x, a);
    a = 0x20;
    writeData(BowserFeetCounter, a);
    writeData(EnemyFrameTimer + x, a);
    a = 0x05;
    writeData(BowserHitPoints, a);
    a >>= 1;
    writeData(BowserMovementSpeed, a);
    goto Return;

//---------------------------------------------------------------------

DuplicateEnemyObj:
    y = 0xff;
FSLoop:
    ++y;
    a = M(Enemy_Flag + y);
    if (!z)
        goto FSLoop;
    writeData(DuplicateObj_Offset, y);
    a = x;
    a |= BOOST_BINARY(10000000);
    writeData(Enemy_Flag + y, a);
    a = M(Enemy_PageLoc + x);
    writeData(Enemy_PageLoc + y, a);
    a = M(Enemy_X_Position + x);
    writeData(Enemy_X_Position + y, a);
    a = 0x01;
    writeData(Enemy_Flag + x, a);
    writeData(Enemy_Y_HighPos + y, a);
    a = M(Enemy_Y_Position + x);
    writeData(Enemy_Y_Position + y, a);
FlmEx:
    goto Return;

//---------------------------------------------------------------------

InitBowserFlame:
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto FlmEx;
    writeData(Enemy_Y_MoveForce + x, a);
    a = M(NoiseSoundQueue);
    a |= Sfx_BowserFlame;
    writeData(NoiseSoundQueue, a);
    y = M(BowserFront_Offset);
    a = M(Enemy_ID + y);
    compare(a, Bowser);
    if (z)
        goto SpawnFromMouth;
    JSR(SetFlameTimer, 285)
    c = 0;
    a += 0x20;
    y = M(SecondaryHardMode);
    if (z)
        goto SetFrT;
    c = 1;
    a -= 0x10;
SetFrT:
    writeData(FrenzyEnemyTimer, a);
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    writeData(BowserFlamePRandomOfs + x, a);
    y = a;
    a = M(FlameYPosData + y);
PutAtRightExtent:
    writeData(Enemy_Y_Position + x, a);
    a = M(ScreenRight_X_Pos);
    c = 0;
    a += 0x20;
    writeData(Enemy_X_Position + x, a);
    a = M(ScreenRight_PageLoc);
    a += 0x00;
    writeData(Enemy_PageLoc + x, a);
    goto FinishFlame;
SpawnFromMouth:
    a = M(Enemy_X_Position + y);
    c = 1;
    a -= 0x0e;
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + y);
    writeData(Enemy_PageLoc + x, a);
    a = M(Enemy_Y_Position + y);
    c = 0;
    a += 0x08;
    writeData(Enemy_Y_Position + x, a);
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    writeData(Enemy_YMF_Dummy + x, a);
    y = a;
    a = M(FlameYPosData + y);
    y = 0x00;
    compare(a, M(Enemy_Y_Position + x));
    if (!c)
        goto SetMF;
    ++y;
SetMF:
    a = M(FlameYMFAdderData + y);
    writeData(Enemy_Y_MoveForce + x, a);
    a = 0x00;
    writeData(EnemyFrenzyBuffer, a);
FinishFlame:
    a = 0x08;
    writeData(Enemy_BoundBoxCtrl + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    a >>= 1;
    writeData(Enemy_X_MoveForce + x, a);
    writeData(Enemy_State + x, a);
    goto Return;

//---------------------------------------------------------------------

InitFireworks:
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto ExitFWk;
    a = 0x20;
    writeData(FrenzyEnemyTimer, a);
    --M(FireworksCounter);
    y = 0x06;
StarFChk:
    --y;
    a = M(Enemy_ID + y);
    compare(a, StarFlagObject);
    if (!z)
        goto StarFChk;
    a = M(Enemy_X_Position + y);
    c = 1;
    a -= 0x30;
    pha();
    a = M(Enemy_PageLoc + y);
    a -= 0x00;
    writeData(0x00, a);
    a = M(FireworksCounter);
    c = 0;
    a += M(Enemy_State + y);
    y = a;
    pla();
    c = 0;
    a += M(FireworksXPosData + y);
    writeData(Enemy_X_Position + x, a);
    a = M(0x00);
    a += 0x00;
    writeData(Enemy_PageLoc + x, a);
    a = M(FireworksYPosData + y);
    writeData(Enemy_Y_Position + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    a >>= 1;
    writeData(ExplosionGfxCounter + x, a);
    a = 0x08;
    writeData(ExplosionTimerCounter + x, a);
ExitFWk:
    goto Return;

//---------------------------------------------------------------------

BulletBillCheepCheep:
    a = M(FrenzyEnemyTimer);
    if (!z)
        goto ExF17;
    a = M(AreaType);
    if (!z)
        goto DoBulletBills;
    compare(x, 0x03);
    if (c)
        goto ExF17;
    y = 0x00;
    a = M(PseudoRandomBitReg + x);
    compare(a, 0xaa);
    if (!c)
        goto ChkW2;
    ++y;
ChkW2:
    a = M(WorldNumber);
    compare(a, World2);
    if (z)
        goto Get17ID;
    ++y;
Get17ID:
    a = y;
    a &= BOOST_BINARY(00000001);
    y = a;
    a = M(SwimCC_IDData + y);
Set17ID:
    writeData(Enemy_ID + x, a);
    a = M(BitMFilter);
    compare(a, 0xff);
    if (!z)
        goto GetRBit;
    a = 0x00;
    writeData(BitMFilter, a);
GetRBit:
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000111);
ChkRBit:
    y = a;
    a = M(Bitmasks + y);
    bit(M(BitMFilter));
    if (z)
        goto AddFBit;
    ++y;
    a = y;
    a &= BOOST_BINARY(00000111);
    goto ChkRBit;
AddFBit:
    a |= M(BitMFilter);
    writeData(BitMFilter, a);
    a = M(Enemy17YPosData + y);
    JSR(PutAtRightExtent, 286)
    writeData(Enemy_YMF_Dummy + x, a);
    a = 0x20;
    writeData(FrenzyEnemyTimer, a);
    goto CheckpointEnemyID;
DoBulletBills:
    y = 0xff;
BB_SLoop:
    ++y;
    compare(y, 0x05);
    if (c)
        goto FireBulletBill;
    a = M(Enemy_Flag + y);
    if (z)
        goto BB_SLoop;
    a = M(Enemy_ID + y);
    compare(a, BulletBill_FrenzyVar);
    if (!z)
        goto BB_SLoop;
ExF17:
    goto Return;

//---------------------------------------------------------------------

FireBulletBill:
    a = M(Square2SoundQueue);
    a |= Sfx_Blast;
    writeData(Square2SoundQueue, a);
    a = BulletBill_FrenzyVar;
    if (!z)
        goto Set17ID;
HandleGroupEnemies:
    y = 0x00;
    c = 1;
    a -= 0x37;
    pha();
    compare(a, 0x04);
    if (c)
        goto SnglID;
    pha();
    y = Goomba;
    a = M(PrimaryHardMode);
    if (z)
        goto PullID;
    y = BuzzyBeetle;
PullID:
    pla();
SnglID:
    writeData(0x01, y);
    y = 0xb0;
    a &= 0x02;
    if (z)
        goto SetYGp;
    y = 0x70;
SetYGp:
    writeData(0x00, y);
    a = M(ScreenRight_PageLoc);
    writeData(0x02, a);
    a = M(ScreenRight_X_Pos);
    writeData(0x03, a);
    y = 0x02;
    pla();
    a >>= 1;
    if (!c)
        goto CntGrp;
    ++y;
CntGrp:
    writeData(NumberofGroupEnemies, y);
GrLoop:
    x = 0xff;
GSltLp:
    ++x;
    compare(x, 0x05);
    if (c)
        goto NextED;
    a = M(Enemy_Flag + x);
    if (!z)
        goto GSltLp;
    a = M(0x01);
    writeData(Enemy_ID + x, a);
    a = M(0x02);
    writeData(Enemy_PageLoc + x, a);
    a = M(0x03);
    writeData(Enemy_X_Position + x, a);
    c = 0;
    a += 0x18;
    writeData(0x03, a);
    a = M(0x02);
    a += 0x00;
    writeData(0x02, a);
    a = M(0x00);
    writeData(Enemy_Y_Position + x, a);
    a = 0x01;
    writeData(Enemy_Y_HighPos + x, a);
    writeData(Enemy_Flag + x, a);
    JSR(CheckpointEnemyID, 287)
    --M(NumberofGroupEnemies);
    if (!z)
        goto GrLoop;
NextED:
    goto Inc2B;
InitPiranhaPlant:
    a = 0x01;
    writeData(PiranhaPlant_Y_Speed + x, a);
    a >>= 1;
    writeData(Enemy_State + x, a);
    writeData(PiranhaPlant_MoveFlag + x, a);
    a = M(Enemy_Y_Position + x);
    writeData(PiranhaPlantDownYPos + x, a);
    c = 1;
    a -= 0x18;
    writeData(PiranhaPlantUpYPos + x, a);
    a = 0x09;
    goto SetBBox2;
InitEnemyFrenzy:
    a = M(Enemy_ID + x);
    writeData(EnemyFrenzyBuffer, a);
    c = 1;
    a -= 0x12;
    switch(a)
        {
    case 0:
        goto LakituAndSpinyHandler;
    case 1:
        goto NoFrenzyCode;
    case 2:
        goto InitFlyingCheepCheep;
    case 3:
        goto InitBowserFlame;
    case 4:
        goto InitFireworks;
    case 5:
        goto BulletBillCheepCheep;
    }
NoFrenzyCode:
    goto Return;

//---------------------------------------------------------------------

EndFrenzy:
    y = 0x05;
LakituChk:
    a = M(Enemy_ID + y);
    compare(a, Lakitu);
    if (!z)
        goto NextFSlot;
    a = 0x01;
    writeData(Enemy_State + y, a);
NextFSlot:
    --y;
    if (!n)
        goto LakituChk;
    a = 0x00;
    writeData(EnemyFrenzyBuffer, a);
    writeData(Enemy_Flag + x, a);
    goto Return;

//---------------------------------------------------------------------

InitJumpGPTroopa:
    a = 0x02;
    writeData(Enemy_MovingDir + x, a);
    a = 0xf8;
    writeData(Enemy_X_Speed + x, a);
TallBBox2:
    a = 0x03;
SetBBox2:
    writeData(Enemy_BoundBoxCtrl + x, a);
    goto Return;

//---------------------------------------------------------------------

InitBalPlatform:
    --M(Enemy_Y_Position + x);
    --M(Enemy_Y_Position + x);
    y = M(SecondaryHardMode);
    if (!z)
        goto AlignP;
    y = 0x02;
    JSR(PosPlatform, 288)
AlignP:
    y = 0xff;
    a = M(BalPlatformAlignment);
    writeData(Enemy_State + x, a);
    if (!n)
        goto SetBPA;
    a = x;
    y = a;
SetBPA:
    writeData(BalPlatformAlignment, y);
    a = 0x00;
    writeData(Enemy_MovingDir + x, a);
    y = a;
    JSR(PosPlatform, 289)
InitDropPlatform:
    a = 0xff;
    writeData(PlatformCollisionFlag + x, a);
    goto CommonPlatCode;
InitHoriPlatform:
    a = 0x00;
    writeData(XMoveSecondaryCounter + x, a);
    goto CommonPlatCode;
InitVertPlatform:
    y = 0x40;
    a = M(Enemy_Y_Position + x);
    if (!n)
        goto SetYO;
    a ^= 0xff;
    c = 0;
    a += 0x01;
    y = 0xc0;
SetYO:
    writeData(YPlatformTopYPos + x, a);
    a = y;
    c = 0;
    a += M(Enemy_Y_Position + x);
    writeData(YPlatformCenterYPos + x, a);
CommonPlatCode:
    JSR(InitVStf, 290)
SPBBox:
    a = 0x05;
    y = M(AreaType);
    compare(y, 0x03);
    if (z)
        goto CasPBB;
    y = M(SecondaryHardMode);
    if (!z)
        goto CasPBB;
    a = 0x06;
CasPBB:
    writeData(Enemy_BoundBoxCtrl + x, a);
    goto Return;

//---------------------------------------------------------------------

LargeLiftUp:
    JSR(PlatLiftUp, 291)
    goto LargeLiftBBox;
LargeLiftDown:
    JSR(PlatLiftDown, 292)
LargeLiftBBox:
    goto SPBBox;
PlatLiftUp:
    a = 0x10;
    writeData(Enemy_Y_MoveForce + x, a);
    a = 0xff;
    writeData(Enemy_Y_Speed + x, a);
    goto CommonSmallLift;
PlatLiftDown:
    a = 0xf0;
    writeData(Enemy_Y_MoveForce + x, a);
    a = 0x00;
    writeData(Enemy_Y_Speed + x, a);
CommonSmallLift:
    y = 0x01;
    JSR(PosPlatform, 293)
    a = 0x04;
    writeData(Enemy_BoundBoxCtrl + x, a);
    goto Return;

//---------------------------------------------------------------------

PosPlatform:
    a = M(Enemy_X_Position + x);
    c = 0;
    a += M(PlatPosDataLow + y);
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a += M(PlatPosDataHigh + y);
    writeData(Enemy_PageLoc + x, a);
    goto Return;

//---------------------------------------------------------------------

EndOfEnemyInitCode:
    goto Return;

//---------------------------------------------------------------------

RunEnemyObjectsCore:
    x = M(ObjectOffset);
    a = 0x00;
    y = M(Enemy_ID + x);
    compare(y, 0x15);
    if (!c)
        goto JmpEO;
    a = y;
    a -= 0x14;
JmpEO:
    switch(a)
        {
    case 0:
        goto RunNormalEnemies;
    case 1:
        goto RunBowserFlame;
    case 2:
        goto RunFireworks;
    case 3:
        goto NoRunCode;
    case 4:
        goto NoRunCode;
    case 5:
        goto NoRunCode;
    case 6:
        goto NoRunCode;
    case 7:
        goto RunFirebarObj;
    case 8:
        goto RunFirebarObj;
    case 9:
        goto RunFirebarObj;
    case 10:
        goto RunFirebarObj;
    case 11:
        goto RunFirebarObj;
    case 12:
        goto RunFirebarObj;
    case 13:
        goto RunFirebarObj;
    case 14:
        goto RunFirebarObj;
    case 15:
        goto NoRunCode;
    case 16:
        goto RunLargePlatform;
    case 17:
        goto RunLargePlatform;
    case 18:
        goto RunLargePlatform;
    case 19:
        goto RunLargePlatform;
    case 20:
        goto RunLargePlatform;
    case 21:
        goto RunLargePlatform;
    case 22:
        goto RunLargePlatform;
    case 23:
        goto RunSmallPlatform;
    case 24:
        goto RunSmallPlatform;
    case 25:
        goto RunBowser;
    case 26:
        goto PowerUpObjHandler;
    case 27:
        goto VineObjectHandler;
    case 28:
        goto NoRunCode;
    case 29:
        goto RunStarFlagObj;
    case 30:
        goto JumpspringHandler;
    case 31:
        goto NoRunCode;
    case 32:
        goto WarpZoneObject;
    case 33:
        goto RunRetainerObj;
    }
NoRunCode:
    goto Return;

//---------------------------------------------------------------------

RunRetainerObj:
    JSR(GetEnemyOffscreenBits, 294)
    JSR(RelativeEnemyPosition, 295)
    goto EnemyGfxHandler;
RunNormalEnemies:
    a = 0x00;
    writeData(Enemy_SprAttrib + x, a);
    JSR(GetEnemyOffscreenBits, 296)
    JSR(RelativeEnemyPosition, 297)
    JSR(EnemyGfxHandler, 298)
    JSR(GetEnemyBoundBox, 299)
    JSR(EnemyToBGCollisionDet, 300)
    JSR(EnemiesCollision, 301)
    JSR(PlayerEnemyCollision, 302)
    y = M(TimerControl);
    if (!z)
        goto SkipMove;
    JSR(EnemyMovementSubs, 303)
SkipMove:
    goto OffscreenBoundsCheck;
EnemyMovementSubs:
    a = M(Enemy_ID + x);
    switch(a)
        {
    case 0:
        goto MoveNormalEnemy;
    case 1:
        goto MoveNormalEnemy;
    case 2:
        goto MoveNormalEnemy;
    case 3:
        goto MoveNormalEnemy;
    case 4:
        goto MoveNormalEnemy;
    case 5:
        goto ProcHammerBro;
    case 6:
        goto MoveNormalEnemy;
    case 7:
        goto MoveBloober;
    case 8:
        goto MoveBulletBill;
    case 9:
        goto NoMoveCode;
    case 10:
        goto MoveSwimmingCheepCheep;
    case 11:
        goto MoveSwimmingCheepCheep;
    case 12:
        goto MovePodoboo;
    case 13:
        goto MovePiranhaPlant;
    case 14:
        goto MoveJumpingEnemy;
    case 15:
        goto ProcMoveRedPTroopa;
    case 16:
        goto MoveFlyGreenPTroopa;
    case 17:
        goto MoveLakitu;
    case 18:
        goto MoveNormalEnemy;
    case 19:
        goto NoMoveCode;
    case 20:
        goto MoveFlyingCheepCheep;
    }
NoMoveCode:
    goto Return;

//---------------------------------------------------------------------

RunBowserFlame:
    JSR(ProcBowserFlame, 304)
    JSR(GetEnemyOffscreenBits, 305)
    JSR(RelativeEnemyPosition, 306)
    JSR(GetEnemyBoundBox, 307)
    JSR(PlayerEnemyCollision, 308)
    goto OffscreenBoundsCheck;
RunFirebarObj:
    JSR(ProcFirebar, 309)
    goto OffscreenBoundsCheck;
RunSmallPlatform:
    JSR(GetEnemyOffscreenBits, 310)
    JSR(RelativeEnemyPosition, 311)
    JSR(SmallPlatformBoundBox, 312)
    JSR(SmallPlatformCollision, 313)
    JSR(RelativeEnemyPosition, 314)
    JSR(DrawSmallPlatform, 315)
    JSR(MoveSmallPlatform, 316)
    goto OffscreenBoundsCheck;
RunLargePlatform:
    JSR(GetEnemyOffscreenBits, 317)
    JSR(RelativeEnemyPosition, 318)
    JSR(LargePlatformBoundBox, 319)
    JSR(LargePlatformCollision, 320)
    a = M(TimerControl);
    if (!z)
        goto SkipPT;
    JSR(LargePlatformSubroutines, 321)
SkipPT:
    JSR(RelativeEnemyPosition, 322)
    JSR(DrawLargePlatform, 323)
    goto OffscreenBoundsCheck;
LargePlatformSubroutines:
    a = M(Enemy_ID + x);
    c = 1;
    a -= 0x24;
    switch(a)
        {
    case 0:
        goto BalancePlatform;
    case 1:
        goto YMovingPlatform;
    case 2:
        goto MoveLargeLiftPlat;
    case 3:
        goto MoveLargeLiftPlat;
    case 4:
        goto XMovingPlatform;
    case 5:
        goto DropPlatform;
    case 6:
        goto RightPlatform;
    }
EraseEnemyObject:
    a = 0x00;
    writeData(Enemy_Flag + x, a);
    writeData(Enemy_ID + x, a);
    writeData(Enemy_State + x, a);
    writeData(FloateyNum_Control + x, a);
    writeData(EnemyIntervalTimer + x, a);
    writeData(ShellChainCounter + x, a);
    writeData(Enemy_SprAttrib + x, a);
    writeData(EnemyFrameTimer + x, a);
    goto Return;

//---------------------------------------------------------------------

MovePodoboo:
    a = M(EnemyIntervalTimer + x);
    if (!z)
        goto PdbM;
    JSR(InitPodoboo, 324)
    a = M(PseudoRandomBitReg + 1 + x);
    a |= BOOST_BINARY(10000000);
    writeData(Enemy_Y_MoveForce + x, a);
    a &= BOOST_BINARY(00001111);
    a |= 0x06;
    writeData(EnemyIntervalTimer + x, a);
    a = 0xf9;
    writeData(Enemy_Y_Speed + x, a);
PdbM:
    goto MoveJ_EnemyVertically;
ProcHammerBro:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto ChkJH;
    goto MoveDefeatedEnemy;
ChkJH:
    a = M(HammerBroJumpTimer + x);
    if (z)
        goto HammerBroJumpCode;
    --M(HammerBroJumpTimer + x);
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001100);
    if (!z)
        goto MoveHammerBroXDir;
    a = M(HammerThrowingTimer + x);
    if (!z)
        goto DecHT;
    y = M(SecondaryHardMode);
    a = M(HammerThrowTmrData + y);
    writeData(HammerThrowingTimer + x, a);
    JSR(SpawnHammerObj, 325)
    if (!c)
        goto DecHT;
    a = M(Enemy_State + x);
    a |= BOOST_BINARY(00001000);
    writeData(Enemy_State + x, a);
    goto MoveHammerBroXDir;
DecHT:
    --M(HammerThrowingTimer + x);
    goto MoveHammerBroXDir;
HammerBroJumpCode:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00000111);
    compare(a, 0x01);
    if (z)
        goto MoveHammerBroXDir;
    a = 0x00;
    writeData(0x00, a);
    y = 0xfa;
    a = M(Enemy_Y_Position + x);
    if (n)
        goto SetHJ;
    y = 0xfd;
    compare(a, 0x70);
    ++M(0x00);
    if (!c)
        goto SetHJ;
    --M(0x00);
    a = M(PseudoRandomBitReg + 1 + x);
    a &= 0x01;
    if (!z)
        goto SetHJ;
    y = 0xfa;
SetHJ:
    writeData(Enemy_Y_Speed + x, y);
    a = M(Enemy_State + x);
    a |= 0x01;
    writeData(Enemy_State + x, a);
    a = M(0x00);
    a &= M(PseudoRandomBitReg + 2 + x);
    y = a;
    a = M(SecondaryHardMode);
    if (!z)
        goto HJump;
    y = a;
HJump:
    a = M(HammerBroJumpLData + y);
    writeData(EnemyFrameTimer + x, a);
    a = M(PseudoRandomBitReg + 1 + x);
    a |= BOOST_BINARY(11000000);
    writeData(HammerBroJumpTimer + x, a);
MoveHammerBroXDir:
    y = 0xfc;
    a = M(FrameCounter);
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto Shimmy;
    y = 0x04;
Shimmy:
    writeData(Enemy_X_Speed + x, y);
    y = 0x01;
    JSR(PlayerEnemyDiff, 326)
    if (n)
        goto SetShim;
    ++y;
    a = M(EnemyIntervalTimer + x);
    if (!z)
        goto SetShim;
    a = 0xf8;
    writeData(Enemy_X_Speed + x, a);
SetShim:
    writeData(Enemy_MovingDir + x, y);
MoveNormalEnemy:
    y = 0x00;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto FallE;
    a = M(Enemy_State + x);
    a <<= 1;
    if (c)
        goto SteadM;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto MoveDefeatedEnemy;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00000111);
    if (z)
        goto SteadM;
    compare(a, 0x05);
    if (z)
        goto FallE;
    compare(a, 0x03);
    if (c)
        goto ReviveStunned;
FallE:
    JSR(MoveD_EnemyVertically, 327)
    y = 0x00;
    a = M(Enemy_State + x);
    compare(a, 0x02);
    if (z)
        goto MEHor;
    a &= BOOST_BINARY(01000000);
    if (z)
        goto SteadM;
    a = M(Enemy_ID + x);
    compare(a, PowerUpObject);
    if (z)
        goto SteadM;
    if (!z)
        goto SlowM;
MEHor:
    goto MoveEnemyHorizontally;
SlowM:
    y = 0x01;
SteadM:
    a = M(Enemy_X_Speed + x);
    pha();
    if (!n)
        goto AddHS;
    ++y;
    ++y;
AddHS:
    c = 0;
    a += M(XSpeedAdderData + y);
    writeData(Enemy_X_Speed + x, a);
    JSR(MoveEnemyHorizontally, 328)
    pla();
    writeData(Enemy_X_Speed + x, a);
    goto Return;

//---------------------------------------------------------------------

ReviveStunned:
    a = M(EnemyIntervalTimer + x);
    if (!z)
        goto ChkKillGoomba;
    writeData(Enemy_State + x, a);
    a = M(FrameCounter);
    a &= 0x01;
    y = a;
    ++y;
    writeData(Enemy_MovingDir + x, y);
    --y;
    a = M(PrimaryHardMode);
    if (z)
        goto SetRSpd;
    ++y;
    ++y;
SetRSpd:
    a = M(RevivedXSpeed + y);
    writeData(Enemy_X_Speed + x, a);
    goto Return;

//---------------------------------------------------------------------

MoveDefeatedEnemy:
    JSR(MoveD_EnemyVertically, 329)
    goto MoveEnemyHorizontally;
ChkKillGoomba:
    compare(a, 0x0e);
    if (!z)
        goto NKGmba;
    a = M(Enemy_ID + x);
    compare(a, Goomba);
    if (!z)
        goto NKGmba;
    JSR(EraseEnemyObject, 330)
NKGmba:
    goto Return;

//---------------------------------------------------------------------

MoveJumpingEnemy:
    JSR(MoveJ_EnemyVertically, 331)
    goto MoveEnemyHorizontally;
ProcMoveRedPTroopa:
    a = M(Enemy_Y_Speed + x);
    a |= M(Enemy_Y_MoveForce + x);
    if (!z)
        goto MoveRedPTUpOrDown;
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    compare(a, M(RedPTroopaOrigXPos + x));
    if (c)
        goto MoveRedPTUpOrDown;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000111);
    if (!z)
        goto NoIncPT;
    ++M(Enemy_Y_Position + x);
NoIncPT:
    goto Return;

//---------------------------------------------------------------------

MoveRedPTUpOrDown:
    a = M(Enemy_Y_Position + x);
    compare(a, M(RedPTroopaCenterYPos + x));
    if (!c)
        goto MovPTDwn;
    goto MoveRedPTroopaUp;
MovPTDwn:
    goto MoveRedPTroopaDown;
MoveFlyGreenPTroopa:
    JSR(XMoveCntr_GreenPTroopa, 332)
    JSR(MoveWithXMCntrs, 333)
    y = 0x01;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000011);
    if (!z)
        goto NoMGPT;
    a = M(FrameCounter);
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto YSway;
    y = 0xff;
YSway:
    writeData(0x00, y);
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += M(0x00);
    writeData(Enemy_Y_Position + x, a);
NoMGPT:
    goto Return;

//---------------------------------------------------------------------

XMoveCntr_GreenPTroopa:
    a = 0x13;
XMoveCntr_Platform:
    writeData(0x01, a);
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000011);
    if (!z)
        goto NoIncXM;
    y = M(XMoveSecondaryCounter + x);
    a = M(XMovePrimaryCounter + x);
    a >>= 1;
    if (c)
        goto DecSeXM;
    compare(y, M(0x01));
    if (z)
        goto IncPXM;
    ++M(XMoveSecondaryCounter + x);
NoIncXM:
    goto Return;

//---------------------------------------------------------------------

IncPXM:
    ++M(XMovePrimaryCounter + x);
    goto Return;

//---------------------------------------------------------------------

DecSeXM:
    a = y;
    if (z)
        goto IncPXM;
    --M(XMoveSecondaryCounter + x);
    goto Return;

//---------------------------------------------------------------------

MoveWithXMCntrs:
    a = M(XMoveSecondaryCounter + x);
    pha();
    y = 0x01;
    a = M(XMovePrimaryCounter + x);
    a &= BOOST_BINARY(00000010);
    if (!z)
        goto XMRight;
    a = M(XMoveSecondaryCounter + x);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(XMoveSecondaryCounter + x, a);
    y = 0x02;
XMRight:
    writeData(Enemy_MovingDir + x, y);
    JSR(MoveEnemyHorizontally, 334)
    writeData(0x00, a);
    pla();
    writeData(XMoveSecondaryCounter + x, a);
    goto Return;

//---------------------------------------------------------------------

MoveBloober:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto MoveDefeatedBloober;
    y = M(SecondaryHardMode);
    a = M(PseudoRandomBitReg + 1 + x);
    a &= M(BlooberBitmasks + y);
    if (!z)
        goto BlooberSwim;
    a = x;
    a >>= 1;
    if (!c)
        goto FBLeft;
    y = M(Player_MovingDir);
    if (c)
        goto SBMDir;
FBLeft:
    y = 0x02;
    JSR(PlayerEnemyDiff, 335)
    if (!n)
        goto SBMDir;
    --y;
SBMDir:
    writeData(Enemy_MovingDir + x, y);
BlooberSwim:
    JSR(ProcSwimmingB, 336)
    a = M(Enemy_Y_Position + x);
    c = 1;
    a -= M(Enemy_Y_MoveForce + x);
    compare(a, 0x20);
    if (!c)
        goto SwimX;
    writeData(Enemy_Y_Position + x, a);
SwimX:
    y = M(Enemy_MovingDir + x);
    --y;
    if (!z)
        goto LeftSwim;
    a = M(Enemy_X_Position + x);
    c = 0;
    a += M(BlooperMoveSpeed + x);
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a += 0x00;
    writeData(Enemy_PageLoc + x, a);
    goto Return;

//---------------------------------------------------------------------

LeftSwim:
    a = M(Enemy_X_Position + x);
    c = 1;
    a -= M(BlooperMoveSpeed + x);
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a -= 0x00;
    writeData(Enemy_PageLoc + x, a);
    goto Return;

//---------------------------------------------------------------------

MoveDefeatedBloober:
    goto MoveEnemySlowVert;
ProcSwimmingB:
    a = M(BlooperMoveCounter + x);
    a &= BOOST_BINARY(00000010);
    if (!z)
        goto ChkForFloatdown;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000111);
    pha();
    a = M(BlooperMoveCounter + x);
    a >>= 1;
    if (c)
        goto SlowSwim;
    pla();
    if (!z)
        goto BSwimE;
    a = M(Enemy_Y_MoveForce + x);
    c = 0;
    a += 0x01;
    writeData(Enemy_Y_MoveForce + x, a);
    writeData(BlooperMoveSpeed + x, a);
    compare(a, 0x02);
    if (!z)
        goto BSwimE;
    ++M(BlooperMoveCounter + x);
BSwimE:
    goto Return;

//---------------------------------------------------------------------

SlowSwim:
    pla();
    if (!z)
        goto NoSSw;
    a = M(Enemy_Y_MoveForce + x);
    c = 1;
    a -= 0x01;
    writeData(Enemy_Y_MoveForce + x, a);
    writeData(BlooperMoveSpeed + x, a);
    if (!z)
        goto NoSSw;
    ++M(BlooperMoveCounter + x);
    a = 0x02;
    writeData(EnemyIntervalTimer + x, a);
NoSSw:
    goto Return;

//---------------------------------------------------------------------

ChkForFloatdown:
    a = M(EnemyIntervalTimer + x);
    if (z)
        goto ChkNearPlayer;
Floatdown:
    a = M(FrameCounter);
    a >>= 1;
    if (c)
        goto NoFD;
    ++M(Enemy_Y_Position + x);
NoFD:
    goto Return;

//---------------------------------------------------------------------

ChkNearPlayer:
    a = M(Enemy_Y_Position + x);
    a += 0x10;
    compare(a, M(Player_Y_Position));
    if (!c)
        goto Floatdown;
    a = 0x00;
    writeData(BlooperMoveCounter + x, a);
    goto Return;

//---------------------------------------------------------------------

MoveBulletBill:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto NotDefB;
    goto MoveJ_EnemyVertically;
NotDefB:
    a = 0xe8;
    writeData(Enemy_X_Speed + x, a);
    goto MoveEnemyHorizontally;
MoveSwimmingCheepCheep:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto CCSwim;
    goto MoveEnemySlowVert;
CCSwim:
    writeData(0x03, a);
    a = M(Enemy_ID + x);
    c = 1;
    a -= 0x0a;
    y = a;
    a = M(SwimCCXMoveData + y);
    writeData(0x02, a);
    a = M(Enemy_X_MoveForce + x);
    c = 1;
    a -= M(0x02);
    writeData(Enemy_X_MoveForce + x, a);
    a = M(Enemy_X_Position + x);
    a -= 0x00;
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a -= 0x00;
    writeData(Enemy_PageLoc + x, a);
    a = 0x20;
    writeData(0x02, a);
    compare(x, 0x02);
    if (!c)
        goto ExSwCC;
    a = M(CheepCheepMoveMFlag + x);
    compare(a, 0x10);
    if (!c)
        goto CCSwimUpwards;
    a = M(Enemy_YMF_Dummy + x);
    c = 0;
    a += M(0x02);
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    a += M(0x03);
    writeData(Enemy_Y_Position + x, a);
    a = M(Enemy_Y_HighPos + x);
    a += 0x00;
    goto ChkSwimYPos;
CCSwimUpwards:
    a = M(Enemy_YMF_Dummy + x);
    c = 1;
    a -= M(0x02);
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    a -= M(0x03);
    writeData(Enemy_Y_Position + x, a);
    a = M(Enemy_Y_HighPos + x);
    a -= 0x00;
ChkSwimYPos:
    writeData(Enemy_Y_HighPos + x, a);
    y = 0x00;
    a = M(Enemy_Y_Position + x);
    c = 1;
    a -= M(CheepCheepOrigYPos + x);
    if (!n)
        goto YPDiff;
    y = 0x10;
    a ^= 0xff;
    c = 0;
    a += 0x01;
YPDiff:
    compare(a, 0x0f);
    if (!c)
        goto ExSwCC;
    a = y;
    writeData(CheepCheepMoveMFlag + x, a);
ExSwCC:
    goto Return;

//---------------------------------------------------------------------

ProcFirebar:
    JSR(GetEnemyOffscreenBits, 337)
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001000);
    if (!z)
        goto SkipFBar;
    a = M(TimerControl);
    if (!z)
        goto SusFbar;
    a = M(FirebarSpinSpeed + x);
    JSR(FirebarSpin, 338)
    a &= BOOST_BINARY(00011111);
    writeData(FirebarSpinState_High + x, a);
SusFbar:
    a = M(FirebarSpinState_High + x);
    y = M(Enemy_ID + x);
    compare(y, 0x1f);
    if (!c)
        goto SetupGFB;
    compare(a, 0x08);
    if (z)
        goto SkpFSte;
    compare(a, 0x18);
    if (!z)
        goto SetupGFB;
SkpFSte:
    c = 0;
    a += 0x01;
    writeData(FirebarSpinState_High + x, a);
SetupGFB:
    writeData(0xef, a);
    JSR(RelativeEnemyPosition, 339)
    JSR(GetFirebarPosition, 340)
    y = M(Enemy_SprDataOffset + x);
    a = M(Enemy_Rel_YPos);
    writeData(Sprite_Y_Position + y, a);
    writeData(0x07, a);
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    writeData(0x06, a);
    a = 0x01;
    writeData(0x00, a);
    JSR(FirebarCollision, 341)
    y = 0x05;
    a = M(Enemy_ID + x);
    compare(a, 0x1f);
    if (!c)
        goto SetMFbar;
    y = 0x0b;
SetMFbar:
    writeData(0xed, y);
    a = 0x00;
    writeData(0x00, a);
DrawFbar:
    a = M(0xef);
    JSR(GetFirebarPosition, 342)
    JSR(DrawFirebar_Collision, 343)
    a = M(0x00);
    compare(a, 0x04);
    if (!z)
        goto NextFbar;
    y = M(DuplicateObj_Offset);
    a = M(Enemy_SprDataOffset + y);
    writeData(0x06, a);
NextFbar:
    ++M(0x00);
    a = M(0x00);
    compare(a, M(0xed));
    if (!c)
        goto DrawFbar;
SkipFBar:
    goto Return;

//---------------------------------------------------------------------

DrawFirebar_Collision:
    a = M(0x03);
    writeData(0x05, a);
    y = M(0x06);
    a = M(0x01);
    M(0x05) >>= 1;
    if (c)
        goto AddHA;
    a ^= 0xff;
    a += 0x01;
AddHA:
    c = 0;
    a += M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    writeData(0x06, a);
    compare(a, M(Enemy_Rel_XPos));
    if (c)
        goto SubtR1;
    a = M(Enemy_Rel_XPos);
    c = 1;
    a -= M(0x06);
    goto ChkFOfs;
SubtR1:
    c = 1;
    a -= M(Enemy_Rel_XPos);
ChkFOfs:
    compare(a, 0x59);
    if (!c)
        goto VAHandl;
    a = 0xf8;
    if (!z)
        goto SetVFbr;
VAHandl:
    a = M(Enemy_Rel_YPos);
    compare(a, 0xf8);
    if (z)
        goto SetVFbr;
    a = M(0x02);
    M(0x05) >>= 1;
    if (c)
        goto AddVA;
    a ^= 0xff;
    a += 0x01;
AddVA:
    c = 0;
    a += M(Enemy_Rel_YPos);
SetVFbr:
    writeData(Sprite_Y_Position + y, a);
    writeData(0x07, a);
FirebarCollision:
    JSR(DrawFirebar, 344)
    a = y;
    pha();
    a = M(StarInvincibleTimer);
    a |= M(TimerControl);
    if (!z)
        goto NoColFB;
    writeData(0x05, a);
    y = M(Player_Y_HighPos);
    --y;
    if (!z)
        goto NoColFB;
    y = M(Player_Y_Position);
    a = M(PlayerSize);
    if (!z)
        goto AdjSm;
    a = M(CrouchingFlag);
    if (z)
        goto BigJp;
AdjSm:
    ++M(0x05);
    ++M(0x05);
    a = y;
    c = 0;
    a += 0x18;
    y = a;
BigJp:
    a = y;
FBCLoop:
    c = 1;
    a -= M(0x07);
    if (!n)
        goto ChkVFBD;
    a ^= 0xff;
    c = 0;
    a += 0x01;
ChkVFBD:
    compare(a, 0x08);
    if (c)
        goto Chk2Ofs;
    a = M(0x06);
    compare(a, 0xf0);
    if (c)
        goto Chk2Ofs;
    a = M(Sprite_X_Position + 4);
    c = 0;
    a += 0x04;
    writeData(0x04, a);
    c = 1;
    a -= M(0x06);
    if (!n)
        goto ChkFBCl;
    a ^= 0xff;
    c = 0;
    a += 0x01;
ChkFBCl:
    compare(a, 0x08);
    if (!c)
        goto ChgSDir;
Chk2Ofs:
    a = M(0x05);
    compare(a, 0x02);
    if (z)
        goto NoColFB;
    y = M(0x05);
    a = M(Player_Y_Position);
    c = 0;
    a += M(FirebarYPos + y);
    ++M(0x05);
    goto FBCLoop;
ChgSDir:
    x = 0x01;
    a = M(0x04);
    compare(a, M(0x06));
    if (c)
        goto SetSDir;
    ++x;
SetSDir:
    writeData(Enemy_MovingDir, x);
    x = 0x00;
    a = M(0x00);
    pha();
    JSR(InjurePlayer, 345)
    pla();
    writeData(0x00, a);
NoColFB:
    pla();
    c = 0;
    a += 0x04;
    writeData(0x06, a);
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

GetFirebarPosition:
    pha();
    a &= BOOST_BINARY(00001111);
    compare(a, 0x09);
    if (!c)
        goto GetHAdder;
    a ^= BOOST_BINARY(00001111);
    c = 0;
    a += 0x01;
GetHAdder:
    writeData(0x01, a);
    y = M(0x00);
    a = M(FirebarTblOffsets + y);
    c = 0;
    a += M(0x01);
    y = a;
    a = M(FirebarPosLookupTbl + y);
    writeData(0x01, a);
    pla();
    pha();
    c = 0;
    a += 0x08;
    a &= BOOST_BINARY(00001111);
    compare(a, 0x09);
    if (!c)
        goto GetVAdder;
    a ^= BOOST_BINARY(00001111);
    c = 0;
    a += 0x01;
GetVAdder:
    writeData(0x02, a);
    y = M(0x00);
    a = M(FirebarTblOffsets + y);
    c = 0;
    a += M(0x02);
    y = a;
    a = M(FirebarPosLookupTbl + y);
    writeData(0x02, a);
    pla();
    a >>= 1;
    a >>= 1;
    a >>= 1;
    y = a;
    a = M(FirebarMirrorData + y);
    writeData(0x03, a);
    goto Return;

//---------------------------------------------------------------------

MoveFlyingCheepCheep:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto FlyCC;
    a = 0x00;
    writeData(Enemy_SprAttrib + x, a);
    goto MoveJ_EnemyVertically;
FlyCC:
    JSR(MoveEnemyHorizontally, 346)
    y = 0x0d;
    a = 0x05;
    JSR(SetXMoveAmt, 347)
    a = M(Enemy_Y_MoveForce + x);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    y = a;
    a = M(Enemy_Y_Position + x);
    c = 1;
    a -= M(PRandomSubtracter + y);
    if (!n)
        goto AddCCF;
    a ^= 0xff;
    c = 0;
    a += 0x01;
AddCCF:
    compare(a, 0x08);
    if (c)
        goto BPGet;
    a = M(Enemy_Y_MoveForce + x);
    c = 0;
    a += 0x10;
    writeData(Enemy_Y_MoveForce + x, a);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    y = a;
BPGet:
    a = M(FlyCCBPriority + y);
    writeData(Enemy_SprAttrib + x, a);
    goto Return;

//---------------------------------------------------------------------

MoveLakitu:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto ChkLS;
    goto MoveD_EnemyVertically;
ChkLS:
    a = M(Enemy_State + x);
    if (z)
        goto Fr12S;
    a = 0x00;
    writeData(LakituMoveDirection + x, a);
    writeData(EnemyFrenzyBuffer, a);
    a = 0x10;
    if (!z)
        goto SetLSpd;
Fr12S:
    a = Spiny;
    writeData(EnemyFrenzyBuffer, a);
    y = 0x02;
LdLDa:
    a = M(LakituDiffAdj + y);
    writeData(0x0001 + y, a);
    --y;
    if (!n)
        goto LdLDa;
    JSR(PlayerLakituDiff, 348)
SetLSpd:
    writeData(LakituMoveSpeed + x, a);
    y = 0x01;
    a = M(LakituMoveDirection + x);
    a &= 0x01;
    if (!z)
        goto SetLMov;
    a = M(LakituMoveSpeed + x);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(LakituMoveSpeed + x, a);
    ++y;
SetLMov:
    writeData(Enemy_MovingDir + x, y);
    goto MoveEnemyHorizontally;
PlayerLakituDiff:
    y = 0x00;
    JSR(PlayerEnemyDiff, 349)
    if (!n)
        goto ChkLakDif;
    ++y;
    a = M(0x00);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(0x00, a);
ChkLakDif:
    a = M(0x00);
    compare(a, 0x3c);
    if (!c)
        goto ChkPSpeed;
    a = 0x3c;
    writeData(0x00, a);
    a = M(Enemy_ID + x);
    compare(a, Lakitu);
    if (!z)
        goto ChkPSpeed;
    a = y;
    compare(a, M(LakituMoveDirection + x));
    if (z)
        goto ChkPSpeed;
    a = M(LakituMoveDirection + x);
    if (z)
        goto SetLMovD;
    --M(LakituMoveSpeed + x);
    a = M(LakituMoveSpeed + x);
    if (!z)
        goto ExMoveLak;
SetLMovD:
    a = y;
    writeData(LakituMoveDirection + x, a);
ChkPSpeed:
    a = M(0x00);
    a &= BOOST_BINARY(00111100);
    a >>= 1;
    a >>= 1;
    writeData(0x00, a);
    y = 0x00;
    a = M(Player_X_Speed);
    if (z)
        goto SubDifAdj;
    a = M(ScrollAmount);
    if (z)
        goto SubDifAdj;
    ++y;
    a = M(Player_X_Speed);
    compare(a, 0x19);
    if (!c)
        goto ChkSpinyO;
    a = M(ScrollAmount);
    compare(a, 0x02);
    if (!c)
        goto ChkSpinyO;
    ++y;
ChkSpinyO:
    a = M(Enemy_ID + x);
    compare(a, Spiny);
    if (!z)
        goto ChkEmySpd;
    a = M(Player_X_Speed);
    if (!z)
        goto SubDifAdj;
ChkEmySpd:
    a = M(Enemy_Y_Speed + x);
    if (!z)
        goto SubDifAdj;
    y = 0x00;
SubDifAdj:
    a = M(0x0001 + y);
    y = M(0x00);
SPixelLak:
    c = 1;
    a -= 0x01;
    --y;
    if (!n)
        goto SPixelLak;
ExMoveLak:
    goto Return;

//---------------------------------------------------------------------

BridgeCollapse:
    x = M(BowserFront_Offset);
    a = M(Enemy_ID + x);
    compare(a, Bowser);
    if (!z)
        goto SetM2;
    writeData(ObjectOffset, x);
    a = M(Enemy_State + x);
    if (z)
        goto RemoveBridge;
    a &= BOOST_BINARY(01000000);
    if (z)
        goto SetM2;
    a = M(Enemy_Y_Position + x);
    compare(a, 0xe0);
    if (!c)
        goto MoveD_Bowser;
SetM2:
    a = Silence;
    writeData(EventMusicQueue, a);
    ++M(OperMode_Task);
    goto KillAllEnemies;
MoveD_Bowser:
    JSR(MoveEnemySlowVert, 350)
    goto BowserGfxHandler;
RemoveBridge:
    --M(BowserFeetCounter);
    if (!z)
        goto NoBFall;
    a = 0x04;
    writeData(BowserFeetCounter, a);
    a = M(BowserBodyControls);
    a ^= 0x01;
    writeData(BowserBodyControls, a);
    a = 0x22;
    writeData(0x05, a);
    y = M(BridgeCollapseOffset);
    a = M(BridgeCollapseData + y);
    writeData(0x04, a);
    y = M(VRAM_Buffer1_Offset);
    ++y;
    x = 0x0c;
    JSR(RemBridge, 351)
    x = M(ObjectOffset);
    JSR(MoveVOffset, 352)
    a = Sfx_Blast;
    writeData(Square2SoundQueue, a);
    a = Sfx_BrickShatter;
    writeData(NoiseSoundQueue, a);
    ++M(BridgeCollapseOffset);
    a = M(BridgeCollapseOffset);
    compare(a, 0x0f);
    if (!z)
        goto NoBFall;
    JSR(InitVStf, 353)
    a = BOOST_BINARY(01000000);
    writeData(Enemy_State + x, a);
    a = Sfx_BowserFall;
    writeData(Square2SoundQueue, a);
NoBFall:
    goto BowserGfxHandler;
RunBowser:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto BowserControl;
    a = M(Enemy_Y_Position + x);
    compare(a, 0xe0);
    if (!c)
        goto MoveD_Bowser;
KillAllEnemies:
    x = 0x04;
KillLoop:
    JSR(EraseEnemyObject, 354)
    --x;
    if (!n)
        goto KillLoop;
    writeData(EnemyFrenzyBuffer, a);
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

BowserControl:
    a = 0x00;
    writeData(EnemyFrenzyBuffer, a);
    a = M(TimerControl);
    if (z)
        goto ChkMouth;
    goto SkipToFB;
ChkMouth:
    a = M(BowserBodyControls);
    if (!n)
        goto FeetTmr;
    goto HammerChk;
FeetTmr:
    --M(BowserFeetCounter);
    if (!z)
        goto ResetMDr;
    a = 0x20;
    writeData(BowserFeetCounter, a);
    a = M(BowserBodyControls);
    a ^= BOOST_BINARY(00000001);
    writeData(BowserBodyControls, a);
ResetMDr:
    a = M(FrameCounter);
    a &= BOOST_BINARY(00001111);
    if (!z)
        goto B_FaceP;
    a = 0x02;
    writeData(Enemy_MovingDir + x, a);
B_FaceP:
    a = M(EnemyFrameTimer + x);
    if (z)
        goto GetPRCmp;
    JSR(PlayerEnemyDiff, 355)
    if (!n)
        goto GetPRCmp;
    a = 0x01;
    writeData(Enemy_MovingDir + x, a);
    a = 0x02;
    writeData(BowserMovementSpeed, a);
    a = 0x20;
    writeData(EnemyFrameTimer + x, a);
    writeData(BowserFireBreathTimer, a);
    a = M(Enemy_X_Position + x);
    compare(a, 0xc8);
    if (c)
        goto HammerChk;
GetPRCmp:
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000011);
    if (!z)
        goto HammerChk;
    a = M(Enemy_X_Position + x);
    compare(a, M(BowserOrigXPos));
    if (!z)
        goto GetDToO;
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    y = a;
    a = M(PRandomRange + y);
    writeData(MaxRangeFromOrigin, a);
GetDToO:
    a = M(Enemy_X_Position + x);
    c = 0;
    a += M(BowserMovementSpeed);
    writeData(Enemy_X_Position + x, a);
    y = M(Enemy_MovingDir + x);
    compare(y, 0x01);
    if (z)
        goto HammerChk;
    y = 0xff;
    c = 1;
    a -= M(BowserOrigXPos);
    if (!n)
        goto CompDToO;
    a ^= 0xff;
    c = 0;
    a += 0x01;
    y = 0x01;
CompDToO:
    compare(a, M(MaxRangeFromOrigin));
    if (!c)
        goto HammerChk;
    writeData(BowserMovementSpeed, y);
HammerChk:
    a = M(EnemyFrameTimer + x);
    if (!z)
        goto MakeBJump;
    JSR(MoveEnemySlowVert, 356)
    a = M(WorldNumber);
    compare(a, World6);
    if (!c)
        goto SetHmrTmr;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000011);
    if (!z)
        goto SetHmrTmr;
    JSR(SpawnHammerObj, 357)
SetHmrTmr:
    a = M(Enemy_Y_Position + x);
    compare(a, 0x80);
    if (!c)
        goto ChkFireB;
    a = M(PseudoRandomBitReg + x);
    a &= BOOST_BINARY(00000011);
    y = a;
    a = M(PRandomRange + y);
    writeData(EnemyFrameTimer + x, a);
SkipToFB:
    goto ChkFireB;
MakeBJump:
    compare(a, 0x01);
    if (!z)
        goto ChkFireB;
    --M(Enemy_Y_Position + x);
    JSR(InitVStf, 358)
    a = 0xfe;
    writeData(Enemy_Y_Speed + x, a);
ChkFireB:
    a = M(WorldNumber);
    compare(a, World8);
    if (z)
        goto SpawnFBr;
    compare(a, World6);
    if (c)
        goto BowserGfxHandler;
SpawnFBr:
    a = M(BowserFireBreathTimer);
    if (!z)
        goto BowserGfxHandler;
    a = 0x20;
    writeData(BowserFireBreathTimer, a);
    a = M(BowserBodyControls);
    a ^= BOOST_BINARY(10000000);
    writeData(BowserBodyControls, a);
    if (n)
        goto ChkFireB;
    JSR(SetFlameTimer, 359)
    y = M(SecondaryHardMode);
    if (z)
        goto SetFBTmr;
    c = 1;
    a -= 0x10;
SetFBTmr:
    writeData(BowserFireBreathTimer, a);
    a = BowserFlame;
    writeData(EnemyFrenzyBuffer, a);
BowserGfxHandler:
    JSR(ProcessBowserHalf, 360)
    y = 0x10;
    a = M(Enemy_MovingDir + x);
    a >>= 1;
    if (!c)
        goto CopyFToR;
    y = 0xf0;
CopyFToR:
    a = y;
    c = 0;
    a += M(Enemy_X_Position + x);
    y = M(DuplicateObj_Offset);
    writeData(Enemy_X_Position + y, a);
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += 0x08;
    writeData(Enemy_Y_Position + y, a);
    a = M(Enemy_State + x);
    writeData(Enemy_State + y, a);
    a = M(Enemy_MovingDir + x);
    writeData(Enemy_MovingDir + y, a);
    a = M(ObjectOffset);
    pha();
    x = M(DuplicateObj_Offset);
    writeData(ObjectOffset, x);
    a = Bowser;
    writeData(Enemy_ID + x, a);
    JSR(ProcessBowserHalf, 361)
    pla();
    writeData(ObjectOffset, a);
    x = a;
    a = 0x00;
    writeData(BowserGfxFlag, a);
ExBGfxH:
    goto Return;

//---------------------------------------------------------------------

ProcessBowserHalf:
    ++M(BowserGfxFlag);
    JSR(RunRetainerObj, 362)
    a = M(Enemy_State + x);
    if (!z)
        goto ExBGfxH;
    a = 0x0a;
    writeData(Enemy_BoundBoxCtrl + x, a);
    JSR(GetEnemyBoundBox, 363)
    goto PlayerEnemyCollision;
SetFlameTimer:
    y = M(BowserFlameTimerCtrl);
    ++M(BowserFlameTimerCtrl);
    a = M(BowserFlameTimerCtrl);
    a &= BOOST_BINARY(00000111);
    writeData(BowserFlameTimerCtrl, a);
    a = M(FlameTimerData + y);
ExFl:
    goto Return;

//---------------------------------------------------------------------

ProcBowserFlame:
    a = M(TimerControl);
    if (!z)
        goto SetGfxF;
    a = 0x40;
    y = M(SecondaryHardMode);
    if (z)
        goto SFlmX;
    a = 0x60;
SFlmX:
    writeData(0x00, a);
    a = M(Enemy_X_MoveForce + x);
    c = 1;
    a -= M(0x00);
    writeData(Enemy_X_MoveForce + x, a);
    a = M(Enemy_X_Position + x);
    a -= 0x01;
    writeData(Enemy_X_Position + x, a);
    a = M(Enemy_PageLoc + x);
    a -= 0x00;
    writeData(Enemy_PageLoc + x, a);
    y = M(BowserFlamePRandomOfs + x);
    a = M(Enemy_Y_Position + x);
    compare(a, M(FlameYPosData + y));
    if (z)
        goto SetGfxF;
    c = 0;
    a += M(Enemy_Y_MoveForce + x);
    writeData(Enemy_Y_Position + x, a);
SetGfxF:
    JSR(RelativeEnemyPosition, 364)
    a = M(Enemy_State + x);
    if (!z)
        goto ExFl;
    a = 0x51;
    writeData(0x00, a);
    y = 0x02;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000010);
    if (z)
        goto FlmeAt;
    y = 0x82;
FlmeAt:
    writeData(0x01, y);
    y = M(Enemy_SprDataOffset + x);
    x = 0x00;
DrawFlameLoop:
    a = M(Enemy_Rel_YPos);
    writeData(Sprite_Y_Position + y, a);
    a = M(0x00);
    writeData(Sprite_Tilenumber + y, a);
    ++M(0x00);
    a = M(0x01);
    writeData(Sprite_Attributes + y, a);
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Enemy_Rel_XPos, a);
    ++y;
    ++y;
    ++y;
    ++y;
    ++x;
    compare(x, 0x03);
    if (!c)
        goto DrawFlameLoop;
    x = M(ObjectOffset);
    JSR(GetEnemyOffscreenBits, 365)
    y = M(Enemy_SprDataOffset + x);
    a = M(Enemy_OffscreenBits);
    a >>= 1;
    pha();
    if (!c)
        goto M3FOfs;
    a = 0xf8;
    writeData(Sprite_Y_Position + 12 + y, a);
M3FOfs:
    pla();
    a >>= 1;
    pha();
    if (!c)
        goto M2FOfs;
    a = 0xf8;
    writeData(Sprite_Y_Position + 8 + y, a);
M2FOfs:
    pla();
    a >>= 1;
    pha();
    if (!c)
        goto M1FOfs;
    a = 0xf8;
    writeData(Sprite_Y_Position + 4 + y, a);
M1FOfs:
    pla();
    a >>= 1;
    if (!c)
        goto ExFlmeD;
    a = 0xf8;
    writeData(Sprite_Y_Position + y, a);
ExFlmeD:
    goto Return;

//---------------------------------------------------------------------

RunFireworks:
    --M(ExplosionTimerCounter + x);
    if (!z)
        goto SetupExpl;
    a = 0x08;
    writeData(ExplosionTimerCounter + x, a);
    ++M(ExplosionGfxCounter + x);
    a = M(ExplosionGfxCounter + x);
    compare(a, 0x03);
    if (c)
        goto FireworksSoundScore;
SetupExpl:
    JSR(RelativeEnemyPosition, 366)
    a = M(Enemy_Rel_YPos);
    writeData(Fireball_Rel_YPos, a);
    a = M(Enemy_Rel_XPos);
    writeData(Fireball_Rel_XPos, a);
    y = M(Enemy_SprDataOffset + x);
    a = M(ExplosionGfxCounter + x);
    JSR(DrawExplosion_Fireworks, 367)
    goto Return;

//---------------------------------------------------------------------

FireworksSoundScore:
    a = 0x00;
    writeData(Enemy_Flag + x, a);
    a = Sfx_Blast;
    writeData(Square2SoundQueue, a);
    a = 0x05;
    writeData(DigitModifier + 4, a);
    goto EndAreaPoints;
RunStarFlagObj:
    a = 0x00;
    writeData(EnemyFrenzyBuffer, a);
    a = M(StarFlagTaskControl);
    compare(a, 0x05);
    if (c)
        goto StarFlagExit;
    switch(a)
        {
    case 0:
        goto StarFlagExit;
    case 1:
        goto GameTimerFireworks;
    case 2:
        goto AwardGameTimerPoints;
    case 3:
        goto RaiseFlagSetoffFWorks;
    case 4:
        goto DelayToAreaEnd;
    }
GameTimerFireworks:
    y = 0x05;
    a = M(GameTimerDisplay + 2);
    compare(a, 0x01);
    if (z)
        goto SetFWC;
    y = 0x03;
    compare(a, 0x03);
    if (z)
        goto SetFWC;
    y = 0x00;
    compare(a, 0x06);
    if (z)
        goto SetFWC;
    a = 0xff;
SetFWC:
    writeData(FireworksCounter, a);
    writeData(Enemy_State + x, y);
IncrementSFTask1:
    ++M(StarFlagTaskControl);
StarFlagExit:
    goto Return;

//---------------------------------------------------------------------

AwardGameTimerPoints:
    a = M(GameTimerDisplay);
    a |= M(GameTimerDisplay + 1);
    a |= M(GameTimerDisplay + 2);
    if (z)
        goto IncrementSFTask1;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000100);
    if (z)
        goto NoTTick;
    a = Sfx_TimerTick;
    writeData(Square2SoundQueue, a);
NoTTick:
    y = 0x23;
    a = 0xff;
    writeData(DigitModifier + 5, a);
    JSR(DigitsMathRoutine, 368)
    a = 0x05;
    writeData(DigitModifier + 5, a);
EndAreaPoints:
    y = 0x0b;
    a = M(CurrentPlayer);
    if (z)
        goto ELPGive;
    y = 0x11;
ELPGive:
    JSR(DigitsMathRoutine, 369)
    a = M(CurrentPlayer);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a |= BOOST_BINARY(00000100);
    goto UpdateNumber;
RaiseFlagSetoffFWorks:
    a = M(Enemy_Y_Position + x);
    compare(a, 0x72);
    if (!c)
        goto SetoffF;
    --M(Enemy_Y_Position + x);
    goto DrawStarFlag;
SetoffF:
    a = M(FireworksCounter);
    if (z)
        goto DrawFlagSetTimer;
    if (n)
        goto DrawFlagSetTimer;
    a = Fireworks;
    writeData(EnemyFrenzyBuffer, a);
DrawStarFlag:
    JSR(RelativeEnemyPosition, 370)
    y = M(Enemy_SprDataOffset + x);
    x = 0x03;
DSFLoop:
    a = M(Enemy_Rel_YPos);
    c = 0;
    a += M(StarFlagYPosAdder + x);
    writeData(Sprite_Y_Position + y, a);
    a = M(StarFlagTileData + x);
    writeData(Sprite_Tilenumber + y, a);
    a = 0x22;
    writeData(Sprite_Attributes + y, a);
    a = M(Enemy_Rel_XPos);
    c = 0;
    a += M(StarFlagXPosAdder + x);
    writeData(Sprite_X_Position + y, a);
    ++y;
    ++y;
    ++y;
    ++y;
    --x;
    if (!n)
        goto DSFLoop;
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

DrawFlagSetTimer:
    JSR(DrawStarFlag, 371)
    a = 0x06;
    writeData(EnemyIntervalTimer + x, a);
IncrementSFTask2:
    ++M(StarFlagTaskControl);
    goto Return;

//---------------------------------------------------------------------

DelayToAreaEnd:
    JSR(DrawStarFlag, 372)
    a = M(EnemyIntervalTimer + x);
    if (!z)
        goto StarFlagExit2;
    a = M(EventMusicBuffer);
    if (z)
        goto IncrementSFTask2;
StarFlagExit2:
    goto Return;

//---------------------------------------------------------------------

MovePiranhaPlant:
    a = M(Enemy_State + x);
    if (!z)
        goto PutinPipe;
    a = M(EnemyFrameTimer + x);
    if (!z)
        goto PutinPipe;
    a = M(PiranhaPlant_MoveFlag + x);
    if (!z)
        goto SetupToMovePPlant;
    a = M(PiranhaPlant_Y_Speed + x);
    if (n)
        goto ReversePlantSpeed;
    JSR(PlayerEnemyDiff, 373)
    if (!n)
        goto ChkPlayerNearPipe;
    a = M(0x00);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(0x00, a);
ChkPlayerNearPipe:
    a = M(0x00);
    compare(a, 0x21);
    if (!c)
        goto PutinPipe;
ReversePlantSpeed:
    a = M(PiranhaPlant_Y_Speed + x);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(PiranhaPlant_Y_Speed + x, a);
    ++M(PiranhaPlant_MoveFlag + x);
SetupToMovePPlant:
    a = M(PiranhaPlantDownYPos + x);
    y = M(PiranhaPlant_Y_Speed + x);
    if (!n)
        goto RiseFallPiranhaPlant;
    a = M(PiranhaPlantUpYPos + x);
RiseFallPiranhaPlant:
    writeData(0x00, a);
    a = M(FrameCounter);
    a >>= 1;
    if (!c)
        goto PutinPipe;
    a = M(TimerControl);
    if (!z)
        goto PutinPipe;
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += M(PiranhaPlant_Y_Speed + x);
    writeData(Enemy_Y_Position + x, a);
    compare(a, M(0x00));
    if (!z)
        goto PutinPipe;
    a = 0x00;
    writeData(PiranhaPlant_MoveFlag + x, a);
    a = 0x40;
    writeData(EnemyFrameTimer + x, a);
PutinPipe:
    a = BOOST_BINARY(00100000);
    writeData(Enemy_SprAttrib + x, a);
    goto Return;

//---------------------------------------------------------------------

FirebarSpin:
    writeData(0x07, a);
    a = M(FirebarSpinDirection + x);
    if (!z)
        goto SpinCounterClockwise;
    y = 0x18;
    a = M(FirebarSpinState_Low + x);
    c = 0;
    a += M(0x07);
    writeData(FirebarSpinState_Low + x, a);
    a = M(FirebarSpinState_High + x);
    a += 0x00;
    goto Return;

//---------------------------------------------------------------------

SpinCounterClockwise:
    y = 0x08;
    a = M(FirebarSpinState_Low + x);
    c = 1;
    a -= M(0x07);
    writeData(FirebarSpinState_Low + x, a);
    a = M(FirebarSpinState_High + x);
    a -= 0x00;
    goto Return;

//---------------------------------------------------------------------

BalancePlatform:
    a = M(Enemy_Y_HighPos + x);
    compare(a, 0x03);
    if (!z)
        goto DoBPl;
    goto EraseEnemyObject;
DoBPl:
    a = M(Enemy_State + x);
    if (!n)
        goto CheckBalPlatform;
    goto Return;

//---------------------------------------------------------------------

CheckBalPlatform:
    y = a;
    a = M(PlatformCollisionFlag + x);
    writeData(0x00, a);
    a = M(Enemy_MovingDir + x);
    if (z)
        goto ChkForFall;
    goto PlatformFall;
ChkForFall:
    a = 0x2d;
    compare(a, M(Enemy_Y_Position + x));
    if (!c)
        goto ChkOtherForFall;
    compare(y, M(0x00));
    if (z)
        goto MakePlatformFall;
    c = 0;
    a += 0x02;
    writeData(Enemy_Y_Position + x, a);
    goto StopPlatforms;
MakePlatformFall:
    goto InitPlatformFall;
ChkOtherForFall:
    compare(a, M(Enemy_Y_Position + y));
    if (!c)
        goto ChkToMoveBalPlat;
    compare(x, M(0x00));
    if (z)
        goto MakePlatformFall;
    c = 0;
    a += 0x02;
    writeData(Enemy_Y_Position + y, a);
    goto StopPlatforms;
ChkToMoveBalPlat:
    a = M(Enemy_Y_Position + x);
    pha();
    a = M(PlatformCollisionFlag + x);
    if (!n)
        goto ColFlg;
    a = M(Enemy_Y_MoveForce + x);
    c = 0;
    a += 0x05;
    writeData(0x00, a);
    a = M(Enemy_Y_Speed + x);
    a += 0x00;
    if (n)
        goto PlatDn;
    if (!z)
        goto PlatUp;
    a = M(0x00);
    compare(a, 0x0b);
    if (!c)
        goto PlatSt;
    if (c)
        goto PlatUp;
ColFlg:
    compare(a, M(ObjectOffset));
    if (z)
        goto PlatDn;
PlatUp:
    JSR(MovePlatformUp, 374)
    goto DoOtherPlatform;
PlatSt:
    JSR(StopPlatforms, 375)
    goto DoOtherPlatform;
PlatDn:
    JSR(MovePlatformDown, 376)
DoOtherPlatform:
    y = M(Enemy_State + x);
    pla();
    c = 1;
    a -= M(Enemy_Y_Position + x);
    c = 0;
    a += M(Enemy_Y_Position + y);
    writeData(Enemy_Y_Position + y, a);
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto DrawEraseRope;
    x = a;
    JSR(PositionPlayerOnVPlat, 377)
DrawEraseRope:
    y = M(ObjectOffset);
    a = M(Enemy_Y_Speed + y);
    a |= M(Enemy_Y_MoveForce + y);
    if (z)
        goto ExitRp;
    x = M(VRAM_Buffer1_Offset);
    compare(x, 0x20);
    if (c)
        goto ExitRp;
    a = M(Enemy_Y_Speed + y);
    pha();
    pha();
    JSR(SetupPlatformRope, 378)
    a = M(0x01);
    writeData(VRAM_Buffer1 + x, a);
    a = M(0x00);
    writeData(VRAM_Buffer1 + 1 + x, a);
    a = 0x02;
    writeData(VRAM_Buffer1 + 2 + x, a);
    a = M(Enemy_Y_Speed + y);
    if (n)
        goto EraseR1;
    a = 0xa2;
    writeData(VRAM_Buffer1 + 3 + x, a);
    a = 0xa3;
    writeData(VRAM_Buffer1 + 4 + x, a);
    goto OtherRope;
EraseR1:
    a = 0x24;
    writeData(VRAM_Buffer1 + 3 + x, a);
    writeData(VRAM_Buffer1 + 4 + x, a);
OtherRope:
    a = M(Enemy_State + y);
    y = a;
    pla();
    a ^= 0xff;
    JSR(SetupPlatformRope, 379)
    a = M(0x01);
    writeData(VRAM_Buffer1 + 5 + x, a);
    a = M(0x00);
    writeData(VRAM_Buffer1 + 6 + x, a);
    a = 0x02;
    writeData(VRAM_Buffer1 + 7 + x, a);
    pla();
    if (!n)
        goto EraseR2;
    a = 0xa2;
    writeData(VRAM_Buffer1 + 8 + x, a);
    a = 0xa3;
    writeData(VRAM_Buffer1 + 9 + x, a);
    goto EndRp;
EraseR2:
    a = 0x24;
    writeData(VRAM_Buffer1 + 8 + x, a);
    writeData(VRAM_Buffer1 + 9 + x, a);
EndRp:
    a = 0x00;
    writeData(VRAM_Buffer1 + 10 + x, a);
    a = M(VRAM_Buffer1_Offset);
    c = 0;
    a += 10;
    writeData(VRAM_Buffer1_Offset, a);
ExitRp:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

SetupPlatformRope:
    pha();
    a = M(Enemy_X_Position + y);
    c = 0;
    a += 0x08;
    x = M(SecondaryHardMode);
    if (!z)
        goto GetLRp;
    c = 0;
    a += 0x10;
GetLRp:
    pha();
    a = M(Enemy_PageLoc + y);
    a += 0x00;
    writeData(0x02, a);
    pla();
    a &= BOOST_BINARY(11110000);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(0x00, a);
    x = M(Enemy_Y_Position + y);
    pla();
    if (!n)
        goto GetHRp;
    a = x;
    c = 0;
    a += 0x08;
    x = a;
GetHRp:
    a = x;
    x = M(VRAM_Buffer1_Offset);
    a <<= 1;
    a.rol();
    pha();
    a.rol();
    a &= BOOST_BINARY(00000011);
    a |= BOOST_BINARY(00100000);
    writeData(0x01, a);
    a = M(0x02);
    a &= 0x01;
    a <<= 1;
    a <<= 1;
    a |= M(0x01);
    writeData(0x01, a);
    pla();
    a &= BOOST_BINARY(11100000);
    c = 0;
    a += M(0x00);
    writeData(0x00, a);
    a = M(Enemy_Y_Position + y);
    compare(a, 0xe8);
    if (!c)
        goto ExPRp;
    a = M(0x00);
    a &= BOOST_BINARY(10111111);
    writeData(0x00, a);
ExPRp:
    goto Return;

//---------------------------------------------------------------------

InitPlatformFall:
    a = y;
    x = a;
    JSR(GetEnemyOffscreenBits, 380)
    a = 0x06;
    JSR(SetupFloateyNumber, 381)
    a = M(Player_Rel_XPos);
    writeData(FloateyNum_X_Pos + x, a);
    a = M(Player_Y_Position);
    writeData(FloateyNum_Y_Pos + x, a);
    a = 0x01;
    writeData(Enemy_MovingDir + x, a);
StopPlatforms:
    JSR(InitVStf, 382)
    writeData(Enemy_Y_Speed + y, a);
    writeData(Enemy_Y_MoveForce + y, a);
    goto Return;

//---------------------------------------------------------------------

PlatformFall:
    a = y;
    pha();
    JSR(MoveFallingPlatform, 383)
    pla();
    x = a;
    JSR(MoveFallingPlatform, 384)
    x = M(ObjectOffset);
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto ExPF;
    x = a;
    JSR(PositionPlayerOnVPlat, 385)
ExPF:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

YMovingPlatform:
    a = M(Enemy_Y_Speed + x);
    a |= M(Enemy_Y_MoveForce + x);
    if (!z)
        goto ChkYCenterPos;
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    compare(a, M(YPlatformTopYPos + x));
    if (c)
        goto ChkYCenterPos;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000111);
    if (!z)
        goto SkipIY;
    ++M(Enemy_Y_Position + x);
SkipIY:
    goto ChkYPCollision;
ChkYCenterPos:
    a = M(Enemy_Y_Position + x);
    compare(a, M(YPlatformCenterYPos + x));
    if (!c)
        goto YMDown;
    JSR(MovePlatformUp, 386)
    goto ChkYPCollision;
YMDown:
    JSR(MovePlatformDown, 387)
ChkYPCollision:
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto ExYPl;
    JSR(PositionPlayerOnVPlat, 388)
ExYPl:
    goto Return;

//---------------------------------------------------------------------

XMovingPlatform:
    a = 0x0e;
    JSR(XMoveCntr_Platform, 389)
    JSR(MoveWithXMCntrs, 390)
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto ExXMP;
PositionPlayerOnHPlat:
    a = M(Player_X_Position);
    c = 0;
    a += M(0x00);
    writeData(Player_X_Position, a);
    a = M(Player_PageLoc);
    y = M(0x00);
    if (n)
        goto PPHSubt;
    a += 0x00;
    goto SetPVar;
PPHSubt:
    a -= 0x00;
SetPVar:
    writeData(Player_PageLoc, a);
    writeData(Platform_X_Scroll, y);
    JSR(PositionPlayerOnVPlat, 391)
ExXMP:
    goto Return;

//---------------------------------------------------------------------

DropPlatform:
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto ExDPl;
    JSR(MoveDropPlatform, 392)
    JSR(PositionPlayerOnVPlat, 393)
ExDPl:
    goto Return;

//---------------------------------------------------------------------

RightPlatform:
    JSR(MoveEnemyHorizontally, 394)
    writeData(0x00, a);
    a = M(PlatformCollisionFlag + x);
    if (n)
        goto ExRPl;
    a = 0x10;
    writeData(Enemy_X_Speed + x, a);
    JSR(PositionPlayerOnHPlat, 395)
ExRPl:
    goto Return;

//---------------------------------------------------------------------

MoveLargeLiftPlat:
    JSR(MoveLiftPlatforms, 396)
    goto ChkYPCollision;
MoveSmallPlatform:
    JSR(MoveLiftPlatforms, 397)
    goto ChkSmallPlatCollision;
MoveLiftPlatforms:
    a = M(TimerControl);
    if (!z)
        goto ExLiftP;
    a = M(Enemy_YMF_Dummy + x);
    c = 0;
    a += M(Enemy_Y_MoveForce + x);
    writeData(Enemy_YMF_Dummy + x, a);
    a = M(Enemy_Y_Position + x);
    a += M(Enemy_Y_Speed + x);
    writeData(Enemy_Y_Position + x, a);
    goto Return;

//---------------------------------------------------------------------

ChkSmallPlatCollision:
    a = M(PlatformCollisionFlag + x);
    if (z)
        goto ExLiftP;
    JSR(PositionPlayerOnS_Plat, 398)
ExLiftP:
    goto Return;

//---------------------------------------------------------------------

OffscreenBoundsCheck:
    a = M(Enemy_ID + x);
    compare(a, FlyingCheepCheep);
    if (z)
        goto ExScrnBd;
    a = M(ScreenLeft_X_Pos);
    y = M(Enemy_ID + x);
    compare(y, HammerBro);
    if (z)
        goto LimitB;
    compare(y, PiranhaPlant);
    if (!z)
        goto ExtendLB;
LimitB:
    a += 0x38;
ExtendLB:
    a -= 0x48;
    writeData(0x01, a);
    a = M(ScreenLeft_PageLoc);
    a -= 0x00;
    writeData(0x00, a);
    a = M(ScreenRight_X_Pos);
    a += 0x48;
    writeData(0x03, a);
    a = M(ScreenRight_PageLoc);
    a += 0x00;
    writeData(0x02, a);
    a = M(Enemy_X_Position + x);
    compare(a, M(0x01));
    a = M(Enemy_PageLoc + x);
    a -= M(0x00);
    if (n)
        goto TooFar;
    a = M(Enemy_X_Position + x);
    compare(a, M(0x03));
    a = M(Enemy_PageLoc + x);
    a -= M(0x02);
    if (n)
        goto ExScrnBd;
    a = M(Enemy_State + x);
    compare(a, HammerBro);
    if (z)
        goto ExScrnBd;
    compare(y, PiranhaPlant);
    if (z)
        goto ExScrnBd;
    compare(y, FlagpoleFlagObject);
    if (z)
        goto ExScrnBd;
    compare(y, StarFlagObject);
    if (z)
        goto ExScrnBd;
    compare(y, JumpspringObject);
    if (z)
        goto ExScrnBd;
TooFar:
    JSR(EraseEnemyObject, 399)
ExScrnBd:
    goto Return;

//---------------------------------------------------------------------

FireballEnemyCollision:
    a = M(Fireball_State + x);
    if (z)
        goto ExitFBallEnemy;
    a <<= 1;
    if (c)
        goto ExitFBallEnemy;
    a = M(FrameCounter);
    a >>= 1;
    if (c)
        goto ExitFBallEnemy;
    a = x;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 0x1c;
    y = a;
    x = 0x04;
FireballEnemyCDLoop:
    writeData(0x01, x);
    a = y;
    pha();
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto NoFToECol;
    a = M(Enemy_Flag + x);
    if (z)
        goto NoFToECol;
    a = M(Enemy_ID + x);
    compare(a, 0x24);
    if (!c)
        goto GoombaDie;
    compare(a, 0x2b);
    if (!c)
        goto NoFToECol;
GoombaDie:
    compare(a, Goomba);
    if (!z)
        goto NotGoomba;
    a = M(Enemy_State + x);
    compare(a, 0x02);
    if (c)
        goto NoFToECol;
NotGoomba:
    a = M(EnemyOffscrBitsMasked + x);
    if (!z)
        goto NoFToECol;
    a = x;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 0x04;
    x = a;
    JSR(SprObjectCollisionCore, 400)
    x = M(ObjectOffset);
    if (!c)
        goto NoFToECol;
    a = BOOST_BINARY(10000000);
    writeData(Fireball_State + x, a);
    x = M(0x01);
    JSR(HandleEnemyFBallCol, 401)
NoFToECol:
    pla();
    y = a;
    x = M(0x01);
    --x;
    if (!n)
        goto FireballEnemyCDLoop;
ExitFBallEnemy:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

HandleEnemyFBallCol:
    JSR(RelativeEnemyPosition, 402)
    x = M(0x01);
    a = M(Enemy_Flag + x);
    if (!n)
        goto ChkBuzzyBeetle;
    a &= BOOST_BINARY(00001111);
    x = a;
    a = M(Enemy_ID + x);
    compare(a, Bowser);
    if (z)
        goto HurtBowser;
    x = M(0x01);
ChkBuzzyBeetle:
    a = M(Enemy_ID + x);
    compare(a, BuzzyBeetle);
    if (z)
        goto ExHCF;
    compare(a, Bowser);
    if (!z)
        goto ChkOtherEnemies;
HurtBowser:
    --M(BowserHitPoints);
    if (!z)
        goto ExHCF;
    JSR(InitVStf, 403)
    writeData(Enemy_X_Speed + x, a);
    writeData(EnemyFrenzyBuffer, a);
    a = 0xfe;
    writeData(Enemy_Y_Speed + x, a);
    y = M(WorldNumber);
    a = M(BowserIdentities + y);
    writeData(Enemy_ID + x, a);
    a = 0x20;
    compare(y, 0x03);
    if (c)
        goto SetDBSte;
    a |= 0x03;
SetDBSte:
    writeData(Enemy_State + x, a);
    a = Sfx_BowserFall;
    writeData(Square2SoundQueue, a);
    x = M(0x01);
    a = 0x09;
    if (!z)
        goto EnemySmackScore;
ChkOtherEnemies:
    compare(a, BulletBill_FrenzyVar);
    if (z)
        goto ExHCF;
    compare(a, Podoboo);
    if (z)
        goto ExHCF;
    compare(a, 0x15);
    if (c)
        goto ExHCF;
ShellOrBlockDefeat:
    a = M(Enemy_ID + x);
    compare(a, PiranhaPlant);
    if (!z)
        goto StnE;
    a = M(Enemy_Y_Position + x);
    a += 0x18;
    writeData(Enemy_Y_Position + x, a);
StnE:
    JSR(ChkToStunEnemies, 404)
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00011111);
    a |= BOOST_BINARY(00100000);
    writeData(Enemy_State + x, a);
    a = 0x02;
    y = M(Enemy_ID + x);
    compare(y, HammerBro);
    if (!z)
        goto GoombaPoints;
    a = 0x06;
GoombaPoints:
    compare(y, Goomba);
    if (!z)
        goto EnemySmackScore;
    a = 0x01;
EnemySmackScore:
    JSR(SetupFloateyNumber, 405)
    a = Sfx_EnemySmack;
    writeData(Square1SoundQueue, a);
ExHCF:
    goto Return;

//---------------------------------------------------------------------

PlayerHammerCollision:
    a = M(FrameCounter);
    a >>= 1;
    if (!c)
        goto ExPHC;
    a = M(TimerControl);
    a |= M(Misc_OffscreenBits);
    if (!z)
        goto ExPHC;
    a = x;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 0x24;
    y = a;
    JSR(PlayerCollisionCore, 406)
    x = M(ObjectOffset);
    if (!c)
        goto ClHCol;
    a = M(Misc_Collision_Flag + x);
    if (!z)
        goto ExPHC;
    a = 0x01;
    writeData(Misc_Collision_Flag + x, a);
    a = M(Misc_X_Speed + x);
    a ^= 0xff;
    c = 0;
    a += 0x01;
    writeData(Misc_X_Speed + x, a);
    a = M(StarInvincibleTimer);
    if (!z)
        goto ExPHC;
    goto InjurePlayer;
ClHCol:
    a = 0x00;
    writeData(Misc_Collision_Flag + x, a);
ExPHC:
    goto Return;

//---------------------------------------------------------------------

HandlePowerUpCollision:
    JSR(EraseEnemyObject, 407)
    a = 0x06;
    JSR(SetupFloateyNumber, 408)
    a = Sfx_PowerUpGrab;
    writeData(Square2SoundQueue, a);
    a = M(PowerUpType);
    compare(a, 0x02);
    if (!c)
        goto Shroom_Flower_PUp;
    compare(a, 0x03);
    if (z)
        goto SetFor1Up;
    a = 0x23;
    writeData(StarInvincibleTimer, a);
    a = StarPowerMusic;
    writeData(AreaMusicQueue, a);
    goto Return;

//---------------------------------------------------------------------

Shroom_Flower_PUp:
    a = M(PlayerStatus);
    if (z)
        goto UpToSuper;
    compare(a, 0x01);
    if (!z)
        goto NoPUp;
    x = M(ObjectOffset);
    a = 0x02;
    writeData(PlayerStatus, a);
    JSR(GetPlayerColors, 409)
    x = M(ObjectOffset);
    a = 0x0c;
    goto UpToFiery;
SetFor1Up:
    a = 0x0b;
    writeData(FloateyNum_Control + x, a);
    goto Return;

//---------------------------------------------------------------------

UpToSuper:
    a = 0x01;
    writeData(PlayerStatus, a);
    a = 0x09;
UpToFiery:
    y = 0x00;
    JSR(SetPRout, 410)
NoPUp:
    goto Return;

//---------------------------------------------------------------------

PlayerEnemyCollision:
    a = M(FrameCounter);
    a >>= 1;
    if (c)
        goto NoPUp;
    JSR(CheckPlayerVertical, 411)
    if (c)
        goto NoPECol;
    a = M(EnemyOffscrBitsMasked + x);
    if (!z)
        goto NoPECol;
    a = M(GameEngineSubroutine);
    compare(a, 0x08);
    if (!z)
        goto NoPECol;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto NoPECol;
    JSR(GetEnemyBoundBoxOfs, 412)
    JSR(PlayerCollisionCore, 413)
    x = M(ObjectOffset);
    if (c)
        goto CheckForPUpCollision;
    a = M(Enemy_CollisionBits + x);
    a &= BOOST_BINARY(11111110);
    writeData(Enemy_CollisionBits + x, a);
NoPECol:
    goto Return;

//---------------------------------------------------------------------

CheckForPUpCollision:
    y = M(Enemy_ID + x);
    compare(y, PowerUpObject);
    if (!z)
        goto EColl;
    goto HandlePowerUpCollision;
EColl:
    a = M(StarInvincibleTimer);
    if (z)
        goto HandlePECollisions;
    goto ShellOrBlockDefeat;
HandlePECollisions:
    a = M(Enemy_CollisionBits + x);
    a &= BOOST_BINARY(00000001);
    a |= M(EnemyOffscrBitsMasked + x);
    if (!z)
        goto ExPEC;
    a = 0x01;
    a |= M(Enemy_CollisionBits + x);
    writeData(Enemy_CollisionBits + x, a);
    compare(y, Spiny);
    if (z)
        goto ChkForPlayerInjury;
    compare(y, PiranhaPlant);
    if (z)
        goto InjurePlayer;
    compare(y, Podoboo);
    if (z)
        goto InjurePlayer;
    compare(y, BulletBill_CannonVar);
    if (z)
        goto ChkForPlayerInjury;
    compare(y, 0x15);
    if (c)
        goto InjurePlayer;
    a = M(AreaType);
    if (z)
        goto InjurePlayer;
    a = M(Enemy_State + x);
    a <<= 1;
    if (c)
        goto ChkForPlayerInjury;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00000111);
    compare(a, 0x02);
    if (!c)
        goto ChkForPlayerInjury;
    a = M(Enemy_ID + x);
    compare(a, Goomba);
    if (z)
        goto ExPEC;
    a = Sfx_EnemySmack;
    writeData(Square1SoundQueue, a);
    a = M(Enemy_State + x);
    a |= BOOST_BINARY(10000000);
    writeData(Enemy_State + x, a);
    JSR(EnemyFacePlayer, 414)
    a = M(KickedShellXSpdData + y);
    writeData(Enemy_X_Speed + x, a);
    a = 0x03;
    c = 0;
    a += M(StompChainCounter);
    y = M(EnemyIntervalTimer + x);
    compare(y, 0x03);
    if (c)
        goto KSPts;
    a = M(KickedShellPtsData + y);
KSPts:
    JSR(SetupFloateyNumber, 415)
ExPEC:
    goto Return;

//---------------------------------------------------------------------

ChkForPlayerInjury:
    a = M(Player_Y_Speed);
    if (n)
        goto ChkInj;
    if (!z)
        goto EnemyStomped;
ChkInj:
    a = M(Enemy_ID + x);
    compare(a, Bloober);
    if (!c)
        goto ChkETmrs;
    a = M(Player_Y_Position);
    c = 0;
    a += 0x0c;
    compare(a, M(Enemy_Y_Position + x));
    if (!c)
        goto EnemyStomped;
ChkETmrs:
    a = M(StompTimer);
    if (!z)
        goto EnemyStomped;
    a = M(InjuryTimer);
    if (!z)
        goto ExInjColRoutines;
    a = M(Player_Rel_XPos);
    compare(a, M(Enemy_Rel_XPos));
    if (!c)
        goto TInjE;
    goto ChkEnemyFaceRight;
TInjE:
    a = M(Enemy_MovingDir + x);
    compare(a, 0x01);
    if (!z)
        goto InjurePlayer;
    goto LInj;
InjurePlayer:
    a = M(InjuryTimer);
    if (!z)
        goto ExInjColRoutines;
ForceInjury:
    x = M(PlayerStatus);
    if (z)
        goto KillPlayer;
    writeData(PlayerStatus, a);
    a = 0x08;
    writeData(InjuryTimer, a);
    a <<= 1;
    writeData(Square1SoundQueue, a);
    JSR(GetPlayerColors, 416)
    a = 0x0a;
SetKRout:
    y = 0x01;
SetPRout:
    writeData(GameEngineSubroutine, a);
    writeData(Player_State, y);
    y = 0xff;
    writeData(TimerControl, y);
    ++y;
    writeData(ScrollAmount, y);
ExInjColRoutines:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

KillPlayer:
    writeData(Player_X_Speed, x);
    ++x;
    writeData(EventMusicQueue, x);
    a = 0xfc;
    writeData(Player_Y_Speed, a);
    a = 0x0b;
    if (!z)
        goto SetKRout;
EnemyStomped:
    a = M(Enemy_ID + x);
    compare(a, Spiny);
    if (z)
        goto InjurePlayer;
    a = Sfx_EnemyStomp;
    writeData(Square1SoundQueue, a);
    a = M(Enemy_ID + x);
    y = 0x00;
    compare(a, FlyingCheepCheep);
    if (z)
        goto EnemyStompedPts;
    compare(a, BulletBill_FrenzyVar);
    if (z)
        goto EnemyStompedPts;
    compare(a, BulletBill_CannonVar);
    if (z)
        goto EnemyStompedPts;
    compare(a, Podoboo);
    if (z)
        goto EnemyStompedPts;
    ++y;
    compare(a, HammerBro);
    if (z)
        goto EnemyStompedPts;
    ++y;
    compare(a, Lakitu);
    if (z)
        goto EnemyStompedPts;
    ++y;
    compare(a, Bloober);
    if (!z)
        goto ChkForDemoteKoopa;
EnemyStompedPts:
    a = M(StompedEnemyPtsData + y);
    JSR(SetupFloateyNumber, 417)
    a = M(Enemy_MovingDir + x);
    pha();
    JSR(SetStun, 418)
    pla();
    writeData(Enemy_MovingDir + x, a);
    a = BOOST_BINARY(00100000);
    writeData(Enemy_State + x, a);
    JSR(InitVStf, 419)
    writeData(Enemy_X_Speed + x, a);
    a = 0xfd;
    writeData(Player_Y_Speed, a);
    goto Return;

//---------------------------------------------------------------------

ChkForDemoteKoopa:
    compare(a, 0x09);
    if (!c)
        goto HandleStompedShellE;
    a &= BOOST_BINARY(00000001);
    writeData(Enemy_ID + x, a);
    y = 0x00;
    writeData(Enemy_State + x, y);
    a = 0x03;
    JSR(SetupFloateyNumber, 420)
    JSR(InitVStf, 421)
    JSR(EnemyFacePlayer, 422)
    a = M(DemotedKoopaXSpdData + y);
    writeData(Enemy_X_Speed + x, a);
    goto SBnce;
HandleStompedShellE:
    a = 0x04;
    writeData(Enemy_State + x, a);
    ++M(StompChainCounter);
    a = M(StompChainCounter);
    c = 0;
    a += M(StompTimer);
    JSR(SetupFloateyNumber, 423)
    ++M(StompTimer);
    y = M(PrimaryHardMode);
    a = M(RevivalRateData + y);
    writeData(EnemyIntervalTimer + x, a);
SBnce:
    a = 0xfc;
    writeData(Player_Y_Speed, a);
    goto Return;

//---------------------------------------------------------------------

ChkEnemyFaceRight:
    a = M(Enemy_MovingDir + x);
    compare(a, 0x01);
    if (!z)
        goto LInj;
    goto InjurePlayer;
LInj:
    JSR(EnemyTurnAround, 424)
    goto InjurePlayer;
EnemyFacePlayer:
    y = 0x01;
    JSR(PlayerEnemyDiff, 425)
    if (!n)
        goto SFcRt;
    ++y;
SFcRt:
    writeData(Enemy_MovingDir + x, y);
    --y;
    goto Return;

//---------------------------------------------------------------------

SetupFloateyNumber:
    writeData(FloateyNum_Control + x, a);
    a = 0x30;
    writeData(FloateyNum_Timer + x, a);
    a = M(Enemy_Y_Position + x);
    writeData(FloateyNum_Y_Pos + x, a);
    a = M(Enemy_Rel_XPos);
    writeData(FloateyNum_X_Pos + x, a);
ExSFN:
    goto Return;

//---------------------------------------------------------------------

EnemiesCollision:
    a = M(FrameCounter);
    a >>= 1;
    if (!c)
        goto ExSFN;
    a = M(AreaType);
    if (z)
        goto ExSFN;
    a = M(Enemy_ID + x);
    compare(a, 0x15);
    if (c)
        goto ExitECRoutine;
    compare(a, Lakitu);
    if (z)
        goto ExitECRoutine;
    compare(a, PiranhaPlant);
    if (z)
        goto ExitECRoutine;
    a = M(EnemyOffscrBitsMasked + x);
    if (!z)
        goto ExitECRoutine;
    JSR(GetEnemyBoundBoxOfs, 426)
    --x;
    if (n)
        goto ExitECRoutine;
ECLoop:
    writeData(0x01, x);
    a = y;
    pha();
    a = M(Enemy_Flag + x);
    if (z)
        goto ReadyNextEnemy;
    a = M(Enemy_ID + x);
    compare(a, 0x15);
    if (c)
        goto ReadyNextEnemy;
    compare(a, Lakitu);
    if (z)
        goto ReadyNextEnemy;
    compare(a, PiranhaPlant);
    if (z)
        goto ReadyNextEnemy;
    a = M(EnemyOffscrBitsMasked + x);
    if (!z)
        goto ReadyNextEnemy;
    a = x;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 0x04;
    x = a;
    JSR(SprObjectCollisionCore, 427)
    x = M(ObjectOffset);
    y = M(0x01);
    if (!c)
        goto NoEnemyCollision;
    a = M(Enemy_State + x);
    a |= M(Enemy_State + y);
    a &= BOOST_BINARY(10000000);
    if (!z)
        goto YesEC;
    a = M(Enemy_CollisionBits + y);
    a &= M(SetBitsMask + x);
    if (!z)
        goto ReadyNextEnemy;
    a = M(Enemy_CollisionBits + y);
    a |= M(SetBitsMask + x);
    writeData(Enemy_CollisionBits + y, a);
YesEC:
    JSR(ProcEnemyCollisions, 428)
    goto ReadyNextEnemy;
NoEnemyCollision:
    a = M(Enemy_CollisionBits + y);
    a &= M(ClearBitsMask + x);
    writeData(Enemy_CollisionBits + y, a);
ReadyNextEnemy:
    pla();
    y = a;
    x = M(0x01);
    --x;
    if (!n)
        goto ECLoop;
ExitECRoutine:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ProcEnemyCollisions:
    a = M(Enemy_State + y);
    a |= M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto ExitProcessEColl;
    a = M(Enemy_State + x);
    compare(a, 0x06);
    if (!c)
        goto ProcSecondEnemyColl;
    a = M(Enemy_ID + x);
    compare(a, HammerBro);
    if (z)
        goto ExitProcessEColl;
    a = M(Enemy_State + y);
    a <<= 1;
    if (!c)
        goto ShellCollisions;
    a = 0x06;
    JSR(SetupFloateyNumber, 429)
    JSR(ShellOrBlockDefeat, 430)
    y = M(0x01);
ShellCollisions:
    a = y;
    x = a;
    JSR(ShellOrBlockDefeat, 431)
    x = M(ObjectOffset);
    a = M(ShellChainCounter + x);
    c = 0;
    a += 0x04;
    x = M(0x01);
    JSR(SetupFloateyNumber, 432)
    x = M(ObjectOffset);
    ++M(ShellChainCounter + x);
ExitProcessEColl:
    goto Return;

//---------------------------------------------------------------------

ProcSecondEnemyColl:
    a = M(Enemy_State + y);
    compare(a, 0x06);
    if (!c)
        goto MoveEOfs;
    a = M(Enemy_ID + y);
    compare(a, HammerBro);
    if (z)
        goto ExitProcessEColl;
    JSR(ShellOrBlockDefeat, 433)
    y = M(0x01);
    a = M(ShellChainCounter + y);
    c = 0;
    a += 0x04;
    x = M(ObjectOffset);
    JSR(SetupFloateyNumber, 434)
    x = M(0x01);
    ++M(ShellChainCounter + x);
    goto Return;

//---------------------------------------------------------------------

MoveEOfs:
    a = y;
    x = a;
    JSR(EnemyTurnAround, 435)
    x = M(ObjectOffset);
EnemyTurnAround:
    a = M(Enemy_ID + x);
    compare(a, PiranhaPlant);
    if (z)
        goto ExTA;
    compare(a, Lakitu);
    if (z)
        goto ExTA;
    compare(a, HammerBro);
    if (z)
        goto ExTA;
    compare(a, Spiny);
    if (z)
        goto RXSpd;
    compare(a, GreenParatroopaJump);
    if (z)
        goto RXSpd;
    compare(a, 0x07);
    if (c)
        goto ExTA;
RXSpd:
    a = M(Enemy_X_Speed + x);
    a ^= 0xff;
    y = a;
    ++y;
    writeData(Enemy_X_Speed + x, y);
    a = M(Enemy_MovingDir + x);
    a ^= BOOST_BINARY(00000011);
    writeData(Enemy_MovingDir + x, a);
ExTA:
    goto Return;

//---------------------------------------------------------------------

LargePlatformCollision:
    a = 0xff;
    writeData(PlatformCollisionFlag + x, a);
    a = M(TimerControl);
    if (!z)
        goto ExLPC;
    a = M(Enemy_State + x);
    if (n)
        goto ExLPC;
    a = M(Enemy_ID + x);
    compare(a, 0x24);
    if (!z)
        goto ChkForPlayerC_LargeP;
    a = M(Enemy_State + x);
    x = a;
    JSR(ChkForPlayerC_LargeP, 436)
ChkForPlayerC_LargeP:
    JSR(CheckPlayerVertical, 437)
    if (c)
        goto ExLPC;
    a = x;
    JSR(GetEnemyBoundBoxOfsArg, 438)
    a = M(Enemy_Y_Position + x);
    writeData(0x00, a);
    a = x;
    pha();
    JSR(PlayerCollisionCore, 439)
    pla();
    x = a;
    if (!c)
        goto ExLPC;
    JSR(ProcLPlatCollisions, 440)
ExLPC:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

SmallPlatformCollision:
    a = M(TimerControl);
    if (!z)
        goto ExSPC;
    writeData(PlatformCollisionFlag + x, a);
    JSR(CheckPlayerVertical, 441)
    if (c)
        goto ExSPC;
    a = 0x02;
    writeData(0x00, a);
ChkSmallPlatLoop:
    x = M(ObjectOffset);
    JSR(GetEnemyBoundBoxOfs, 442)
    a &= BOOST_BINARY(00000010);
    if (!z)
        goto ExSPC;
    a = M(BoundingBox_UL_YPos + y);
    compare(a, 0x20);
    if (!c)
        goto MoveBoundBox;
    JSR(PlayerCollisionCore, 443)
    if (c)
        goto ProcSPlatCollisions;
MoveBoundBox:
    a = M(BoundingBox_UL_YPos + y);
    c = 0;
    a += 0x80;
    writeData(BoundingBox_UL_YPos + y, a);
    a = M(BoundingBox_DR_YPos + y);
    c = 0;
    a += 0x80;
    writeData(BoundingBox_DR_YPos + y, a);
    --M(0x00);
    if (!z)
        goto ChkSmallPlatLoop;
ExSPC:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

ProcSPlatCollisions:
    x = M(ObjectOffset);
ProcLPlatCollisions:
    a = M(BoundingBox_DR_YPos + y);
    c = 1;
    a -= M(BoundingBox_UL_YPos);
    compare(a, 0x04);
    if (c)
        goto ChkForTopCollision;
    a = M(Player_Y_Speed);
    if (!n)
        goto ChkForTopCollision;
    a = 0x01;
    writeData(Player_Y_Speed, a);
ChkForTopCollision:
    a = M(BoundingBox_DR_YPos);
    c = 1;
    a -= M(BoundingBox_UL_YPos + y);
    compare(a, 0x06);
    if (c)
        goto PlatformSideCollisions;
    a = M(Player_Y_Speed);
    if (n)
        goto PlatformSideCollisions;
    a = M(0x00);
    y = M(Enemy_ID + x);
    compare(y, 0x2b);
    if (z)
        goto SetCollisionFlag;
    compare(y, 0x2c);
    if (z)
        goto SetCollisionFlag;
    a = x;
SetCollisionFlag:
    x = M(ObjectOffset);
    writeData(PlatformCollisionFlag + x, a);
    a = 0x00;
    writeData(Player_State, a);
    goto Return;

//---------------------------------------------------------------------

PlatformSideCollisions:
    a = 0x01;
    writeData(0x00, a);
    a = M(BoundingBox_DR_XPos);
    c = 1;
    a -= M(BoundingBox_UL_XPos + y);
    compare(a, 0x08);
    if (!c)
        goto SideC;
    ++M(0x00);
    a = M(BoundingBox_DR_XPos + y);
    c = 0;
    a -= M(BoundingBox_UL_XPos);
    compare(a, 0x09);
    if (c)
        goto NoSideC;
SideC:
    JSR(ImpedePlayerMove, 444)
NoSideC:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

PositionPlayerOnS_Plat:
    y = a;
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += M(PlayerPosSPlatData - 1 + y);
    goto Skip_8;
PositionPlayerOnVPlat:
    a = M(Enemy_Y_Position + x);
Skip_8:
    y = M(GameEngineSubroutine);
    compare(y, 0x0b);
    if (z)
        goto ExPlPos;
    y = M(Enemy_Y_HighPos + x);
    compare(y, 0x01);
    if (!z)
        goto ExPlPos;
    c = 1;
    a -= 0x20;
    writeData(Player_Y_Position, a);
    a = y;
    a -= 0x00;
    writeData(Player_Y_HighPos, a);
    a = 0x00;
    writeData(Player_Y_Speed, a);
    writeData(Player_Y_MoveForce, a);
ExPlPos:
    goto Return;

//---------------------------------------------------------------------

CheckPlayerVertical:
    a = M(Player_OffscreenBits);
    compare(a, 0xf0);
    if (c)
        goto ExCPV;
    y = M(Player_Y_HighPos);
    --y;
    if (!z)
        goto ExCPV;
    a = M(Player_Y_Position);
    compare(a, 0xd0);
ExCPV:
    goto Return;

//---------------------------------------------------------------------

GetEnemyBoundBoxOfs:
    a = M(ObjectOffset);
GetEnemyBoundBoxOfsArg:
    a <<= 1;
    a <<= 1;
    c = 0;
    a += 0x04;
    y = a;
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001111);
    compare(a, BOOST_BINARY(00001111));
    goto Return;

//---------------------------------------------------------------------

PlayerBGCollision:
    a = M(DisableCollisionDet);
    if (!z)
        goto ExPBGCol;
    a = M(GameEngineSubroutine);
    compare(a, 0x0b);
    if (z)
        goto ExPBGCol;
    compare(a, 0x04);
    if (!c)
        goto ExPBGCol;
    a = 0x01;
    y = M(SwimmingFlag);
    if (!z)
        goto SetPSte;
    a = M(Player_State);
    if (z)
        goto SetFallS;
    compare(a, 0x03);
    if (!z)
        goto ChkOnScr;
SetFallS:
    a = 0x02;
SetPSte:
    writeData(Player_State, a);
ChkOnScr:
    a = M(Player_Y_HighPos);
    compare(a, 0x01);
    if (!z)
        goto ExPBGCol;
    a = 0xff;
    writeData(Player_CollisionBits, a);
    a = M(Player_Y_Position);
    compare(a, 0xcf);
    if (!c)
        goto ChkCollSize;
ExPBGCol:
    goto Return;

//---------------------------------------------------------------------

ChkCollSize:
    y = 0x02;
    a = M(CrouchingFlag);
    if (!z)
        goto GBBAdr;
    a = M(PlayerSize);
    if (!z)
        goto GBBAdr;
    --y;
    a = M(SwimmingFlag);
    if (!z)
        goto GBBAdr;
    --y;
GBBAdr:
    a = M(BlockBufferAdderData + y);
    writeData(0xeb, a);
    y = a;
    x = M(PlayerSize);
    a = M(CrouchingFlag);
    if (z)
        goto HeadChk;
    ++x;
HeadChk:
    a = M(Player_Y_Position);
    compare(a, M(PlayerBGUpperExtent + x));
    if (!c)
        goto DoFootCheck;
    JSR(BlockBufferColli_Head, 445)
    if (z)
        goto DoFootCheck;
    JSR(CheckForCoinMTiles, 446)
    if (c)
        goto AwardTouchedCoin;
    y = M(Player_Y_Speed);
    if (!n)
        goto DoFootCheck;
    y = M(0x04);
    compare(y, 0x04);
    if (!c)
        goto DoFootCheck;
    JSR(CheckForSolidMTiles, 447)
    if (c)
        goto SolidOrClimb;
    y = M(AreaType);
    if (z)
        goto NYSpd;
    y = M(BlockBounceTimer);
    if (!z)
        goto NYSpd;
    JSR(PlayerHeadCollision, 448)
    goto DoFootCheck;
SolidOrClimb:
    compare(a, 0x26);
    if (z)
        goto NYSpd;
    a = Sfx_Bump;
    writeData(Square1SoundQueue, a);
NYSpd:
    a = 0x01;
    writeData(Player_Y_Speed, a);
DoFootCheck:
    y = M(0xeb);
    a = M(Player_Y_Position);
    compare(a, 0xcf);
    if (c)
        goto DoPlayerSideCheck;
    JSR(BlockBufferColli_Feet, 449)
    JSR(CheckForCoinMTiles, 450)
    if (c)
        goto AwardTouchedCoin;
    pha();
    JSR(BlockBufferColli_Feet, 451)
    writeData(0x00, a);
    pla();
    writeData(0x01, a);
    if (!z)
        goto ChkFootMTile;
    a = M(0x00);
    if (z)
        goto DoPlayerSideCheck;
    JSR(CheckForCoinMTiles, 452)
    if (!c)
        goto ChkFootMTile;
AwardTouchedCoin:
    goto HandleCoinMetatile;
ChkFootMTile:
    JSR(CheckForClimbMTiles, 453)
    if (c)
        goto DoPlayerSideCheck;
    y = M(Player_Y_Speed);
    if (n)
        goto DoPlayerSideCheck;
    compare(a, 0xc5);
    if (!z)
        goto ContChk;
    goto HandleAxeMetatile;
ContChk:
    JSR(ChkInvisibleMTiles, 454)
    if (z)
        goto DoPlayerSideCheck;
    y = M(JumpspringAnimCtrl);
    if (!z)
        goto InitSteP;
    y = M(0x04);
    compare(y, 0x05);
    if (!c)
        goto LandPlyr;
    a = M(Player_MovingDir);
    writeData(0x00, a);
    goto ImpedePlayerMove;
LandPlyr:
    JSR(ChkForLandJumpSpring, 455)
    a = 0xf0;
    a &= M(Player_Y_Position);
    writeData(Player_Y_Position, a);
    JSR(HandlePipeEntry, 456)
    a = 0x00;
    writeData(Player_Y_Speed, a);
    writeData(Player_Y_MoveForce, a);
    writeData(StompChainCounter, a);
InitSteP:
    a = 0x00;
    writeData(Player_State, a);
DoPlayerSideCheck:
    y = M(0xeb);
    ++y;
    ++y;
    a = 0x02;
    writeData(0x00, a);
SideCheckLoop:
    ++y;
    writeData(0xeb, y);
    a = M(Player_Y_Position);
    compare(a, 0x20);
    if (!c)
        goto BHalf;
    compare(a, 0xe4);
    if (c)
        goto ExSCH;
    JSR(BlockBufferColli_Side, 457)
    if (z)
        goto BHalf;
    compare(a, 0x1c);
    if (z)
        goto BHalf;
    compare(a, 0x6b);
    if (z)
        goto BHalf;
    JSR(CheckForClimbMTiles, 458)
    if (!c)
        goto CheckSideMTiles;
BHalf:
    y = M(0xeb);
    ++y;
    a = M(Player_Y_Position);
    compare(a, 0x08);
    if (!c)
        goto ExSCH;
    compare(a, 0xd0);
    if (c)
        goto ExSCH;
    JSR(BlockBufferColli_Side, 459)
    if (!z)
        goto CheckSideMTiles;
    --M(0x00);
    if (!z)
        goto SideCheckLoop;
ExSCH:
    goto Return;

//---------------------------------------------------------------------

CheckSideMTiles:
    JSR(ChkInvisibleMTiles, 460)
    if (z)
        goto ExCSM;
    JSR(CheckForClimbMTiles, 461)
    if (!c)
        goto ContSChk;
    goto HandleClimbing;
ContSChk:
    JSR(CheckForCoinMTiles, 462)
    if (c)
        goto HandleCoinMetatile;
    JSR(ChkJumpspringMetatiles, 463)
    if (!c)
        goto ChkPBtm;
    a = M(JumpspringAnimCtrl);
    if (!z)
        goto ExCSM;
    goto StopPlayerMove;
ChkPBtm:
    y = M(Player_State);
    compare(y, 0x00);
    if (!z)
        goto StopPlayerMove;
    y = M(PlayerFacingDir);
    --y;
    if (!z)
        goto StopPlayerMove;
    compare(a, 0x6c);
    if (z)
        goto PipeDwnS;
    compare(a, 0x1f);
    if (!z)
        goto StopPlayerMove;
PipeDwnS:
    a = M(Player_SprAttrib);
    if (!z)
        goto PlyrPipe;
    y = Sfx_PipeDown_Injury;
    writeData(Square1SoundQueue, y);
PlyrPipe:
    a |= BOOST_BINARY(00100000);
    writeData(Player_SprAttrib, a);
    a = M(Player_X_Position);
    a &= BOOST_BINARY(00001111);
    if (z)
        goto ChkGERtn;
    y = 0x00;
    a = M(ScreenLeft_PageLoc);
    if (z)
        goto SetCATmr;
    ++y;
SetCATmr:
    a = M(AreaChangeTimerData + y);
    writeData(ChangeAreaTimer, a);
ChkGERtn:
    a = M(GameEngineSubroutine);
    compare(a, 0x07);
    if (z)
        goto ExCSM;
    compare(a, 0x08);
    if (!z)
        goto ExCSM;
    a = 0x02;
    writeData(GameEngineSubroutine, a);
    goto Return;

//---------------------------------------------------------------------

StopPlayerMove:
    JSR(ImpedePlayerMove, 464)
ExCSM:
    goto Return;

//---------------------------------------------------------------------

HandleCoinMetatile:
    JSR(ErACM, 465)
    ++M(CoinTallyFor1Ups);
    goto GiveOneCoin;
HandleAxeMetatile:
    a = 0x00;
    writeData(OperMode_Task, a);
    a = 0x02;
    writeData(OperMode, a);
    a = 0x18;
    writeData(Player_X_Speed, a);
ErACM:
    y = M(0x02);
    a = 0x00;
    writeData(W(0x06) + y, a);
    goto RemoveCoin_Axe;
HandleClimbing:
    y = M(0x04);
    compare(y, 0x06);
    if (!c)
        goto ExHC;
    compare(y, 0x0a);
    if (!c)
        goto ChkForFlagpole;
ExHC:
    goto Return;

//---------------------------------------------------------------------

ChkForFlagpole:
    compare(a, 0x24);
    if (z)
        goto FlagpoleCollision;
    compare(a, 0x25);
    if (!z)
        goto VineCollision;
FlagpoleCollision:
    a = M(GameEngineSubroutine);
    compare(a, 0x05);
    if (z)
        goto PutPlayerOnVine;
    a = 0x01;
    writeData(PlayerFacingDir, a);
    ++M(ScrollLock);
    a = M(GameEngineSubroutine);
    compare(a, 0x04);
    if (z)
        goto RunFR;
    a = BulletBill_CannonVar;
    JSR(KillEnemies, 466)
    a = Silence;
    writeData(EventMusicQueue, a);
    a >>= 1;
    writeData(FlagpoleSoundQueue, a);
    x = 0x04;
    a = M(Player_Y_Position);
    writeData(FlagpoleCollisionYPos, a);
ChkFlagpoleYPosLoop:
    compare(a, M(FlagpoleYPosData + x));
    if (c)
        goto MtchF;
    --x;
    if (!z)
        goto ChkFlagpoleYPosLoop;
MtchF:
    writeData(FlagpoleScore, x);
RunFR:
    a = 0x04;
    writeData(GameEngineSubroutine, a);
    goto PutPlayerOnVine;
VineCollision:
    compare(a, 0x26);
    if (!z)
        goto PutPlayerOnVine;
    a = M(Player_Y_Position);
    compare(a, 0x20);
    if (c)
        goto PutPlayerOnVine;
    a = 0x01;
    writeData(GameEngineSubroutine, a);
PutPlayerOnVine:
    a = 0x03;
    writeData(Player_State, a);
    a = 0x00;
    writeData(Player_X_Speed, a);
    writeData(Player_X_MoveForce, a);
    a = M(Player_X_Position);
    c = 1;
    a -= M(ScreenLeft_X_Pos);
    compare(a, 0x10);
    if (c)
        goto SetVXPl;
    a = 0x02;
    writeData(PlayerFacingDir, a);
SetVXPl:
    y = M(PlayerFacingDir);
    a = M(0x06);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    c = 0;
    a += M(ClimbXPosAdder - 1 + y);
    writeData(Player_X_Position, a);
    a = M(0x06);
    if (!z)
        goto ExPVne;
    a = M(ScreenRight_PageLoc);
    c = 0;
    a += M(ClimbPLocAdder - 1 + y);
    writeData(Player_PageLoc, a);
ExPVne:
    goto Return;

//---------------------------------------------------------------------

ChkInvisibleMTiles:
    compare(a, 0x5f);
    if (z)
        goto ExCInvT;
    compare(a, 0x60);
ExCInvT:
    goto Return;

//---------------------------------------------------------------------

ChkForLandJumpSpring:
    JSR(ChkJumpspringMetatiles, 467)
    if (!c)
        goto ExCJSp;
    a = 0x70;
    writeData(VerticalForce, a);
    a = 0xf9;
    writeData(JumpspringForce, a);
    a = 0x03;
    writeData(JumpspringTimer, a);
    a >>= 1;
    writeData(JumpspringAnimCtrl, a);
ExCJSp:
    goto Return;

//---------------------------------------------------------------------

ChkJumpspringMetatiles:
    compare(a, 0x67);
    if (z)
        goto JSFnd;
    compare(a, 0x68);
    c = 0;
    if (!z)
        goto NoJSFnd;
JSFnd:
    c = 1;
NoJSFnd:
    goto Return;

//---------------------------------------------------------------------

HandlePipeEntry:
    a = M(Up_Down_Buttons);
    a &= BOOST_BINARY(00000100);
    if (z)
        goto ExPipeE;
    a = M(0x00);
    compare(a, 0x11);
    if (!z)
        goto ExPipeE;
    a = M(0x01);
    compare(a, 0x10);
    if (!z)
        goto ExPipeE;
    a = 0x30;
    writeData(ChangeAreaTimer, a);
    a = 0x03;
    writeData(GameEngineSubroutine, a);
    a = Sfx_PipeDown_Injury;
    writeData(Square1SoundQueue, a);
    a = BOOST_BINARY(00100000);
    writeData(Player_SprAttrib, a);
    a = M(WarpZoneControl);
    if (z)
        goto ExPipeE;
    a &= BOOST_BINARY(00000011);
    a <<= 1;
    a <<= 1;
    x = a;
    a = M(Player_X_Position);
    compare(a, 0x60);
    if (!c)
        goto GetWNum;
    ++x;
    compare(a, 0xa0);
    if (!c)
        goto GetWNum;
    ++x;
GetWNum:
    y = M(WarpZoneNumbers + x);
    --y;
    writeData(WorldNumber, y);
    x = M(WorldAddrOffsets + y);
    a = M(AreaAddrOffsets + x);
    writeData(AreaPointer, a);
    a = Silence;
    writeData(EventMusicQueue, a);
    a = 0x00;
    writeData(EntrancePage, a);
    writeData(AreaNumber, a);
    writeData(LevelNumber, a);
    writeData(AltEntranceControl, a);
    ++M(Hidden1UpFlag);
    ++M(FetchNewGameTimerFlag);
ExPipeE:
    goto Return;

//---------------------------------------------------------------------

ImpedePlayerMove:
    a = 0x00;
    y = M(Player_X_Speed);
    x = M(0x00);
    --x;
    if (!z)
        goto RImpd;
    ++x;
    compare(y, 0x00);
    if (n)
        goto ExIPM;
    a = 0xff;
    goto NXSpd;
RImpd:
    x = 0x02;
    compare(y, 0x01);
    if (!n)
        goto ExIPM;
    a = 0x01;
NXSpd:
    y = 0x10;
    writeData(SideCollisionTimer, y);
    y = 0x00;
    writeData(Player_X_Speed, y);
    compare(a, 0x00);
    if (!n)
        goto PlatF;
    --y;
PlatF:
    writeData(0x00, y);
    c = 0;
    a += M(Player_X_Position);
    writeData(Player_X_Position, a);
    a = M(Player_PageLoc);
    a += M(0x00);
    writeData(Player_PageLoc, a);
ExIPM:
    a = x;
    a ^= 0xff;
    a &= M(Player_CollisionBits);
    writeData(Player_CollisionBits, a);
    goto Return;

//---------------------------------------------------------------------

CheckForSolidMTiles:
    JSR(GetMTileAttrib, 468)
    compare(a, M(SolidMTileUpperExt + x));
    goto Return;

//---------------------------------------------------------------------

CheckForClimbMTiles:
    JSR(GetMTileAttrib, 469)
    compare(a, M(ClimbMTileUpperExt + x));
    goto Return;

//---------------------------------------------------------------------

CheckForCoinMTiles:
    compare(a, 0xc2);
    if (z)
        goto CoinSd;
    compare(a, 0xc3);
    if (z)
        goto CoinSd;
    c = 0;
    goto Return;

//---------------------------------------------------------------------

CoinSd:
    a = Sfx_CoinGrab;
    writeData(Square2SoundQueue, a);
    goto Return;

//---------------------------------------------------------------------

GetMTileAttrib:
    y = a;
    a &= BOOST_BINARY(11000000);
    a <<= 1;
    a.rol();
    a.rol();
    x = a;
    a = y;
ExEBG:
    goto Return;

//---------------------------------------------------------------------

EnemyToBGCollisionDet:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto ExEBG;
    JSR(SubtEnemyYPos, 470)
    if (!c)
        goto ExEBG;
    y = M(Enemy_ID + x);
    compare(y, Spiny);
    if (!z)
        goto DoIDCheckBGColl;
    a = M(Enemy_Y_Position + x);
    compare(a, 0x25);
    if (!c)
        goto ExEBG;
DoIDCheckBGColl:
    compare(y, GreenParatroopaJump);
    if (!z)
        goto HBChk;
    goto EnemyJump;
HBChk:
    compare(y, HammerBro);
    if (!z)
        goto CInvu;
    goto HammerBroBGColl;
CInvu:
    compare(y, Spiny);
    if (z)
        goto YesIn;
    compare(y, PowerUpObject);
    if (z)
        goto YesIn;
    compare(y, 0x07);
    if (c)
        goto ExEBGChk;
YesIn:
    JSR(ChkUnderEnemy, 471)
    if (!z)
        goto HandleEToBGCollision;
NoEToBGCollision:
    goto ChkForRedKoopa;
HandleEToBGCollision:
    JSR(ChkForNonSolids, 472)
    if (z)
        goto NoEToBGCollision;
    compare(a, 0x23);
    if (!z)
        goto LandEnemyProperly;
    y = M(0x02);
    a = 0x00;
    writeData(W(0x06) + y, a);
    a = M(Enemy_ID + x);
    compare(a, 0x15);
    if (c)
        goto ChkToStunEnemies;
    compare(a, Goomba);
    if (!z)
        goto GiveOEPoints;
    JSR(KillEnemyAboveBlock, 473)
GiveOEPoints:
    a = 0x01;
    JSR(SetupFloateyNumber, 474)
ChkToStunEnemies:
    compare(a, 0x09);
    if (!c)
        goto SetStun;
    compare(a, 0x11);
    if (c)
        goto SetStun;
    compare(a, 0x0a);
    if (!c)
        goto Demote;
    compare(a, PiranhaPlant);
    if (!c)
        goto SetStun;
Demote:
    a &= BOOST_BINARY(00000001);
    writeData(Enemy_ID + x, a);
SetStun:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(11110000);
    a |= BOOST_BINARY(00000010);
    writeData(Enemy_State + x, a);
    --M(Enemy_Y_Position + x);
    --M(Enemy_Y_Position + x);
    a = M(Enemy_ID + x);
    compare(a, Bloober);
    if (z)
        goto SetWYSpd;
    a = 0xfd;
    y = M(AreaType);
    if (!z)
        goto SetNotW;
SetWYSpd:
    a = 0xff;
SetNotW:
    writeData(Enemy_Y_Speed + x, a);
    y = 0x01;
    JSR(PlayerEnemyDiff, 475)
    if (!n)
        goto ChkBBill;
    ++y;
ChkBBill:
    a = M(Enemy_ID + x);
    compare(a, BulletBill_CannonVar);
    if (z)
        goto NoCDirF;
    compare(a, BulletBill_FrenzyVar);
    if (z)
        goto NoCDirF;
    writeData(Enemy_MovingDir + x, y);
NoCDirF:
    --y;
    a = M(EnemyBGCXSpdData + y);
    writeData(Enemy_X_Speed + x, a);
ExEBGChk:
    goto Return;

//---------------------------------------------------------------------

LandEnemyProperly:
    a = M(0x04);
    c = 1;
    a -= 0x08;
    compare(a, 0x05);
    if (c)
        goto ChkForRedKoopa;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(01000000);
    if (!z)
        goto LandEnemyInitState;
    a = M(Enemy_State + x);
    a <<= 1;
    if (!c)
        goto ChkLandedEnemyState;
SChkA:
    goto DoEnemySideCheck;
ChkLandedEnemyState:
    a = M(Enemy_State + x);
    if (z)
        goto SChkA;
    compare(a, 0x05);
    if (z)
        goto ProcEnemyDirection;
    compare(a, 0x03);
    if (c)
        goto ExSteChk;
    a = M(Enemy_State + x);
    compare(a, 0x02);
    if (!z)
        goto ProcEnemyDirection;
    a = 0x10;
    y = M(Enemy_ID + x);
    compare(y, Spiny);
    if (!z)
        goto SetForStn;
    a = 0x00;
SetForStn:
    writeData(EnemyIntervalTimer + x, a);
    a = 0x03;
    writeData(Enemy_State + x, a);
    JSR(EnemyLanding, 476)
ExSteChk:
    goto Return;

//---------------------------------------------------------------------

ProcEnemyDirection:
    a = M(Enemy_ID + x);
    compare(a, Goomba);
    if (z)
        goto LandEnemyInitState;
    compare(a, Spiny);
    if (!z)
        goto InvtD;
    a = 0x01;
    writeData(Enemy_MovingDir + x, a);
    a = 0x08;
    writeData(Enemy_X_Speed + x, a);
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000111);
    if (z)
        goto LandEnemyInitState;
InvtD:
    y = 0x01;
    JSR(PlayerEnemyDiff, 477)
    if (!n)
        goto CNwCDir;
    ++y;
CNwCDir:
    a = y;
    compare(a, M(Enemy_MovingDir + x));
    if (!z)
        goto LandEnemyInitState;
    JSR(ChkForBump_HammerBroJ, 478)
LandEnemyInitState:
    JSR(EnemyLanding, 479)
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(10000000);
    if (!z)
        goto NMovShellFallBit;
    a = 0x00;
    writeData(Enemy_State + x, a);
    goto Return;

//---------------------------------------------------------------------

NMovShellFallBit:
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(10111111);
    writeData(Enemy_State + x, a);
    goto Return;

//---------------------------------------------------------------------

ChkForRedKoopa:
    a = M(Enemy_ID + x);
    compare(a, RedKoopa);
    if (!z)
        goto Chk2MSBSt;
    a = M(Enemy_State + x);
    if (z)
        goto ChkForBump_HammerBroJ;
Chk2MSBSt:
    a = M(Enemy_State + x);
    y = a;
    a <<= 1;
    if (!c)
        goto GetSteFromD;
    a = M(Enemy_State + x);
    a |= BOOST_BINARY(01000000);
    goto SetD6Ste;
GetSteFromD:
    a = M(EnemyBGCStateData + y);
SetD6Ste:
    writeData(Enemy_State + x, a);
DoEnemySideCheck:
    a = M(Enemy_Y_Position + x);
    compare(a, 0x20);
    if (!c)
        goto ExESdeC;
    y = 0x16;
    a = 0x02;
    writeData(0xeb, a);
SdeCLoop:
    a = M(0xeb);
    compare(a, M(Enemy_MovingDir + x));
    if (!z)
        goto NextSdeC;
    a = 0x01;
    JSR(BlockBufferChk_Enemy, 480)
    if (z)
        goto NextSdeC;
    JSR(ChkForNonSolids, 481)
    if (!z)
        goto ChkForBump_HammerBroJ;
NextSdeC:
    --M(0xeb);
    ++y;
    compare(y, 0x18);
    if (!c)
        goto SdeCLoop;
ExESdeC:
    goto Return;

//---------------------------------------------------------------------

ChkForBump_HammerBroJ:
    compare(x, 0x05);
    if (z)
        goto NoBump;
    a = M(Enemy_State + x);
    a <<= 1;
    if (!c)
        goto NoBump;
    a = Sfx_Bump;
    writeData(Square1SoundQueue, a);
NoBump:
    a = M(Enemy_ID + x);
    compare(a, 0x05);
    if (!z)
        goto InvEnemyDir;
    a = 0x00;
    writeData(0x00, a);
    y = 0xfa;
    goto SetHJ;
InvEnemyDir:
    goto RXSpd;
PlayerEnemyDiff:
    a = M(Enemy_X_Position + x);
    c = 1;
    a -= M(Player_X_Position);
    writeData(0x00, a);
    a = M(Enemy_PageLoc + x);
    a -= M(Player_PageLoc);
    goto Return;

//---------------------------------------------------------------------

EnemyLanding:
    JSR(InitVStf, 482)
    a = M(Enemy_Y_Position + x);
    a &= BOOST_BINARY(11110000);
    a |= BOOST_BINARY(00001000);
    writeData(Enemy_Y_Position + x, a);
    goto Return;

//---------------------------------------------------------------------

SubtEnemyYPos:
    a = M(Enemy_Y_Position + x);
    c = 0;
    a += 0x3e;
    compare(a, 0x44);
    goto Return;

//---------------------------------------------------------------------

EnemyJump:
    JSR(SubtEnemyYPos, 483)
    if (!c)
        goto DoSide;
    a = M(Enemy_Y_Speed + x);
    c = 0;
    a += 0x02;
    compare(a, 0x03);
    if (!c)
        goto DoSide;
    JSR(ChkUnderEnemy, 484)
    if (z)
        goto DoSide;
    JSR(ChkForNonSolids, 485)
    if (z)
        goto DoSide;
    JSR(EnemyLanding, 486)
    a = 0xfd;
    writeData(Enemy_Y_Speed + x, a);
DoSide:
    goto DoEnemySideCheck;
HammerBroBGColl:
    JSR(ChkUnderEnemy, 487)
    if (z)
        goto NoUnderHammerBro;
    compare(a, 0x23);
    if (!z)
        goto UnderHammerBro;
KillEnemyAboveBlock:
    JSR(ShellOrBlockDefeat, 488)
    a = 0xfc;
    writeData(Enemy_Y_Speed + x, a);
    goto Return;

//---------------------------------------------------------------------

UnderHammerBro:
    a = M(EnemyFrameTimer + x);
    if (!z)
        goto NoUnderHammerBro;
    a = M(Enemy_State + x);
    a &= BOOST_BINARY(10001000);
    writeData(Enemy_State + x, a);
    JSR(EnemyLanding, 489)
    goto DoEnemySideCheck;
NoUnderHammerBro:
    a = M(Enemy_State + x);
    a |= 0x01;
    writeData(Enemy_State + x, a);
    goto Return;

//---------------------------------------------------------------------

ChkUnderEnemy:
    a = 0x00;
    y = 0x15;
    goto BlockBufferChk_Enemy;
ChkForNonSolids:
    compare(a, 0x26);
    if (z)
        goto NSFnd;
    compare(a, 0xc2);
    if (z)
        goto NSFnd;
    compare(a, 0xc3);
    if (z)
        goto NSFnd;
    compare(a, 0x5f);
    if (z)
        goto NSFnd;
    compare(a, 0x60);
NSFnd:
    goto Return;

//---------------------------------------------------------------------

FireballBGCollision:
    a = M(Fireball_Y_Position + x);
    compare(a, 0x18);
    if (!c)
        goto ClearBounceFlag;
    JSR(BlockBufferChk_FBall, 490)
    if (z)
        goto ClearBounceFlag;
    JSR(ChkForNonSolids, 491)
    if (z)
        goto ClearBounceFlag;
    a = M(Fireball_Y_Speed + x);
    if (n)
        goto InitFireballExplode;
    a = M(FireballBouncingFlag + x);
    if (!z)
        goto InitFireballExplode;
    a = 0xfd;
    writeData(Fireball_Y_Speed + x, a);
    a = 0x01;
    writeData(FireballBouncingFlag + x, a);
    a = M(Fireball_Y_Position + x);
    a &= 0xf8;
    writeData(Fireball_Y_Position + x, a);
    goto Return;

//---------------------------------------------------------------------

ClearBounceFlag:
    a = 0x00;
    writeData(FireballBouncingFlag + x, a);
    goto Return;

//---------------------------------------------------------------------

InitFireballExplode:
    a = 0x80;
    writeData(Fireball_State + x, a);
    a = Sfx_Bump;
    writeData(Square1SoundQueue, a);
    goto Return;

//---------------------------------------------------------------------

GetFireballBoundBox:
    a = x;
    c = 0;
    a += 0x07;
    x = a;
    y = 0x02;
    if (!z)
        goto FBallB;
GetMiscBoundBox:
    a = x;
    c = 0;
    a += 0x09;
    x = a;
    y = 0x06;
FBallB:
    JSR(BoundingBoxCore, 492)
    goto CheckRightScreenBBox;
GetEnemyBoundBox:
    y = 0x48;
    writeData(0x00, y);
    y = 0x44;
    goto GetMaskedOffScrBits;
SmallPlatformBoundBox:
    y = 0x08;
    writeData(0x00, y);
    y = 0x04;
GetMaskedOffScrBits:
    a = M(Enemy_X_Position + x);
    c = 1;
    a -= M(ScreenLeft_X_Pos);
    writeData(0x01, a);
    a = M(Enemy_PageLoc + x);
    a -= M(ScreenLeft_PageLoc);
    if (n)
        goto CMBits;
    a |= M(0x01);
    if (z)
        goto CMBits;
    y = M(0x00);
CMBits:
    a = y;
    a &= M(Enemy_OffscreenBits);
    writeData(EnemyOffscrBitsMasked + x, a);
    if (!z)
        goto MoveBoundBoxOffscreen;
    goto SetupEOffsetFBBox;
LargePlatformBoundBox:
    ++x;
    JSR(GetXOffscreenBits, 493)
    --x;
    compare(a, 0xfe);
    if (c)
        goto MoveBoundBoxOffscreen;
SetupEOffsetFBBox:
    a = x;
    c = 0;
    a += 0x01;
    x = a;
    y = 0x01;
    JSR(BoundingBoxCore, 494)
    goto CheckRightScreenBBox;
MoveBoundBoxOffscreen:
    a = x;
    a <<= 1;
    a <<= 1;
    y = a;
    a = 0xff;
    writeData(EnemyBoundingBoxCoord + y, a);
    writeData(EnemyBoundingBoxCoord + 1 + y, a);
    writeData(EnemyBoundingBoxCoord + 2 + y, a);
    writeData(EnemyBoundingBoxCoord + 3 + y, a);
    goto Return;

//---------------------------------------------------------------------

BoundingBoxCore:
    writeData(0x00, x);
    a = M(SprObject_Rel_YPos + y);
    writeData(0x02, a);
    a = M(SprObject_Rel_XPos + y);
    writeData(0x01, a);
    a = x;
    a <<= 1;
    a <<= 1;
    pha();
    y = a;
    a = M(SprObj_BoundBoxCtrl + x);
    a <<= 1;
    a <<= 1;
    x = a;
    a = M(0x01);
    c = 0;
    a += M(BoundBoxCtrlData + x);
    writeData(BoundingBox_UL_Corner + y, a);
    a = M(0x01);
    c = 0;
    a += M(BoundBoxCtrlData + 2 + x);
    writeData(BoundingBox_LR_Corner + y, a);
    ++x;
    ++y;
    a = M(0x02);
    c = 0;
    a += M(BoundBoxCtrlData + x);
    writeData(BoundingBox_UL_Corner + y, a);
    a = M(0x02);
    c = 0;
    a += M(BoundBoxCtrlData + 2 + x);
    writeData(BoundingBox_LR_Corner + y, a);
    pla();
    y = a;
    x = M(0x00);
    goto Return;

//---------------------------------------------------------------------

CheckRightScreenBBox:
    a = M(ScreenLeft_X_Pos);
    c = 0;
    a += 0x80;
    writeData(0x02, a);
    a = M(ScreenLeft_PageLoc);
    a += 0x00;
    writeData(0x01, a);
    a = M(SprObject_X_Position + x);
    compare(a, M(0x02));
    a = M(SprObject_PageLoc + x);
    a -= M(0x01);
    if (!c)
        goto CheckLeftScreenBBox;
    a = M(BoundingBox_DR_XPos + y);
    if (n)
        goto NoOfs;
    a = 0xff;
    x = M(BoundingBox_UL_XPos + y);
    if (n)
        goto SORte;
    writeData(BoundingBox_UL_XPos + y, a);
SORte:
    writeData(BoundingBox_DR_XPos + y, a);
NoOfs:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

CheckLeftScreenBBox:
    a = M(BoundingBox_UL_XPos + y);
    if (!n)
        goto NoOfs2;
    compare(a, 0xa0);
    if (!c)
        goto NoOfs2;
    a = 0x00;
    x = M(BoundingBox_DR_XPos + y);
    if (!n)
        goto SOLft;
    writeData(BoundingBox_DR_XPos + y, a);
SOLft:
    writeData(BoundingBox_UL_XPos + y, a);
NoOfs2:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

PlayerCollisionCore:
    x = 0x00;
SprObjectCollisionCore:
    writeData(0x06, y);
    a = 0x01;
    writeData(0x07, a);
CollisionCoreLoop:
    a = M(BoundingBox_UL_Corner + y);
    compare(a, M(BoundingBox_UL_Corner + x));
    if (c)
        goto FirstBoxGreater;
    compare(a, M(BoundingBox_LR_Corner + x));
    if (!c)
        goto SecondBoxVerticalChk;
    if (z)
        goto CollisionFound;
    a = M(BoundingBox_LR_Corner + y);
    compare(a, M(BoundingBox_UL_Corner + y));
    if (!c)
        goto CollisionFound;
    compare(a, M(BoundingBox_UL_Corner + x));
    if (c)
        goto CollisionFound;
    y = M(0x06);
    goto Return;

//---------------------------------------------------------------------

SecondBoxVerticalChk:
    a = M(BoundingBox_LR_Corner + x);
    compare(a, M(BoundingBox_UL_Corner + x));
    if (!c)
        goto CollisionFound;
    a = M(BoundingBox_LR_Corner + y);
    compare(a, M(BoundingBox_UL_Corner + x));
    if (c)
        goto CollisionFound;
    y = M(0x06);
    goto Return;

//---------------------------------------------------------------------

FirstBoxGreater:
    compare(a, M(BoundingBox_UL_Corner + x));
    if (z)
        goto CollisionFound;
    compare(a, M(BoundingBox_LR_Corner + x));
    if (!c)
        goto CollisionFound;
    if (z)
        goto CollisionFound;
    compare(a, M(BoundingBox_LR_Corner + y));
    if (!c)
        goto NoCollisionFound;
    if (z)
        goto NoCollisionFound;
    a = M(BoundingBox_LR_Corner + y);
    compare(a, M(BoundingBox_UL_Corner + x));
    if (c)
        goto CollisionFound;
NoCollisionFound:
    c = 0;
    y = M(0x06);
    goto Return;

//---------------------------------------------------------------------

CollisionFound:
    ++x;
    ++y;
    --M(0x07);
    if (!n)
        goto CollisionCoreLoop;
    c = 1;
    y = M(0x06);
    goto Return;

//---------------------------------------------------------------------

BlockBufferChk_Enemy:
    pha();
    a = x;
    c = 0;
    a += 0x01;
    x = a;
    pla();
    goto BBChk_E;
ResidualMiscObjectCode:
    a = x;
    c = 0;
    a += 0x0d;
    x = a;
    y = 0x1b;
    goto ResJmpM;
BlockBufferChk_FBall:
    y = 0x1a;
    a = x;
    c = 0;
    a += 0x07;
    x = a;
ResJmpM:
    a = 0x00;
BBChk_E:
    JSR(BlockBufferCollision, 495)
    x = M(ObjectOffset);
    compare(a, 0x00);
    goto Return;

//---------------------------------------------------------------------

BlockBufferColli_Feet:
    ++y;
BlockBufferColli_Head:
    a = 0x00;
    goto Skip_9;
BlockBufferColli_Side:
    a = 0x01;
Skip_9:
    x = 0x00;
BlockBufferCollision:
    pha();
    writeData(0x04, y);
    a = M(BlockBuffer_X_Adder + y);
    c = 0;
    a += M(SprObject_X_Position + x);
    writeData(0x05, a);
    a = M(SprObject_PageLoc + x);
    a += 0x00;
    a &= 0x01;
    a >>= 1;
    a |= M(0x05);
    a.ror();
    a >>= 1;
    a >>= 1;
    a >>= 1;
    JSR(GetBlockBufferAddr, 496)
    y = M(0x04);
    a = M(SprObject_Y_Position + x);
    c = 0;
    a += M(BlockBuffer_Y_Adder + y);
    a &= BOOST_BINARY(11110000);
    c = 1;
    a -= 0x20;
    writeData(0x02, a);
    y = a;
    a = M(W(0x06) + y);
    writeData(0x03, a);
    y = M(0x04);
    pla();
    if (!z)
        goto RetXC;
    a = M(SprObject_Y_Position + x);
    goto RetYC;
RetXC:
    a = M(SprObject_X_Position + x);
RetYC:
    a &= BOOST_BINARY(00001111);
    writeData(0x04, a);
    a = M(0x03);
    goto Return;

//---------------------------------------------------------------------

DrawVine:
    writeData(0x00, y);
    a = M(Enemy_Rel_YPos);
    c = 0;
    a += M(VineYPosAdder + y);
    x = M(VineObjOffset + y);
    y = M(Enemy_SprDataOffset + x);
    writeData(0x02, y);
    JSR(SixSpriteStacker, 497)
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    writeData(Sprite_X_Position + 8 + y, a);
    writeData(Sprite_X_Position + 16 + y, a);
    c = 0;
    a += 0x06;
    writeData(Sprite_X_Position + 4 + y, a);
    writeData(Sprite_X_Position + 12 + y, a);
    writeData(Sprite_X_Position + 20 + y, a);
    a = BOOST_BINARY(00100001);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 16 + y, a);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + 12 + y, a);
    writeData(Sprite_Attributes + 20 + y, a);
    x = 0x05;
VineTL:
    a = 0xe1;
    writeData(Sprite_Tilenumber + y, a);
    ++y;
    ++y;
    ++y;
    ++y;
    --x;
    if (!n)
        goto VineTL;
    y = M(0x02);
    a = M(0x00);
    if (!z)
        goto SkpVTop;
    a = 0xe0;
    writeData(Sprite_Tilenumber + y, a);
SkpVTop:
    x = 0x00;
ChkFTop:
    a = M(VineStart_Y_Position);
    c = 1;
    a -= M(Sprite_Y_Position + y);
    compare(a, 0x64);
    if (!c)
        goto NextVSp;
    a = 0xf8;
    writeData(Sprite_Y_Position + y, a);
NextVSp:
    ++y;
    ++y;
    ++y;
    ++y;
    ++x;
    compare(x, 0x06);
    if (!z)
        goto ChkFTop;
    y = M(0x00);
    goto Return;

//---------------------------------------------------------------------

SixSpriteStacker:
    x = 0x06;
StkLp:
    writeData(Sprite_Data + y, a);
    c = 0;
    a += 0x08;
    ++y;
    ++y;
    ++y;
    ++y;
    --x;
    if (!z)
        goto StkLp;
    y = M(0x02);
    goto Return;

//---------------------------------------------------------------------

DrawHammer:
    y = M(Misc_SprDataOffset + x);
    a = M(TimerControl);
    if (!z)
        goto ForceHPose;
    a = M(Misc_State + x);
    a &= BOOST_BINARY(01111111);
    compare(a, 0x01);
    if (z)
        goto GetHPose;
ForceHPose:
    x = 0x00;
    if (z)
        goto RenderH;
GetHPose:
    a = M(FrameCounter);
    a >>= 1;
    a >>= 1;
    a &= BOOST_BINARY(00000011);
    x = a;
RenderH:
    a = M(Misc_Rel_YPos);
    c = 0;
    a += M(FirstSprYPos + x);
    writeData(Sprite_Y_Position + y, a);
    c = 0;
    a += M(SecondSprYPos + x);
    writeData(Sprite_Y_Position + 4 + y, a);
    a = M(Misc_Rel_XPos);
    c = 0;
    a += M(FirstSprXPos + x);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += M(SecondSprXPos + x);
    writeData(Sprite_X_Position + 4 + y, a);
    a = M(FirstSprTilenum + x);
    writeData(Sprite_Tilenumber + y, a);
    a = M(SecondSprTilenum + x);
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = M(HammerSprAttrib + x);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    x = M(ObjectOffset);
    a = M(Misc_OffscreenBits);
    a &= BOOST_BINARY(11111100);
    if (z)
        goto NoHOffscr;
    a = 0x00;
    writeData(Misc_State + x, a);
    a = 0xf8;
    JSR(DumpTwoSpr, 498)
NoHOffscr:
    goto Return;

//---------------------------------------------------------------------

FlagpoleGfxHandler:
    y = M(Enemy_SprDataOffset + x);
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 4 + y, a);
    writeData(Sprite_X_Position + 8 + y, a);
    c = 0;
    a += 0x0c;
    writeData(0x05, a);
    a = M(Enemy_Y_Position + x);
    JSR(DumpTwoSpr, 499)
    a += 0x08;
    writeData(Sprite_Y_Position + 8 + y, a);
    a = M(FlagpoleFNum_Y_Pos);
    writeData(0x02, a);
    a = 0x01;
    writeData(0x03, a);
    writeData(0x04, a);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + 8 + y, a);
    a = 0x7e;
    writeData(Sprite_Tilenumber + y, a);
    writeData(Sprite_Tilenumber + 8 + y, a);
    a = 0x7f;
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = M(FlagpoleCollisionYPos);
    if (z)
        goto ChkFlagOffscreen;
    a = y;
    c = 0;
    a += 0x0c;
    y = a;
    a = M(FlagpoleScore);
    a <<= 1;
    x = a;
    a = M(FlagpoleScoreNumTiles + x);
    writeData(0x00, a);
    a = M(FlagpoleScoreNumTiles + 1 + x);
    JSR(DrawOneSpriteRow, 500)
ChkFlagOffscreen:
    x = M(ObjectOffset);
    y = M(Enemy_SprDataOffset + x);
    a = M(Enemy_OffscreenBits);
    a &= BOOST_BINARY(00001110);
    if (z)
        goto ExitDumpSpr;
MoveSixSpritesOffscreen:
    a = 0xf8;
DumpSixSpr:
    writeData(Sprite_Data + 20 + y, a);
    writeData(Sprite_Data + 16 + y, a);
DumpFourSpr:
    writeData(Sprite_Data + 12 + y, a);
DumpThreeSpr:
    writeData(Sprite_Data + 8 + y, a);
DumpTwoSpr:
    writeData(Sprite_Data + 4 + y, a);
    writeData(Sprite_Data + y, a);
ExitDumpSpr:
    goto Return;

//---------------------------------------------------------------------

DrawLargePlatform:
    y = M(Enemy_SprDataOffset + x);
    writeData(0x02, y);
    ++y;
    ++y;
    ++y;
    a = M(Enemy_Rel_XPos);
    JSR(SixSpriteStacker, 501)
    x = M(ObjectOffset);
    a = M(Enemy_Y_Position + x);
    JSR(DumpFourSpr, 502)
    y = M(AreaType);
    compare(y, 0x03);
    if (z)
        goto ShrinkPlatform;
    y = M(SecondaryHardMode);
    if (z)
        goto SetLast2Platform;
ShrinkPlatform:
    a = 0xf8;
SetLast2Platform:
    y = M(Enemy_SprDataOffset + x);
    writeData(Sprite_Y_Position + 16 + y, a);
    writeData(Sprite_Y_Position + 20 + y, a);
    a = 0x5b;
    x = M(CloudTypeOverride);
    if (z)
        goto SetPlatformTilenum;
    a = 0x75;
SetPlatformTilenum:
    x = M(ObjectOffset);
    ++y;
    JSR(DumpSixSpr, 503)
    a = 0x02;
    ++y;
    JSR(DumpSixSpr, 504)
    ++x;
    JSR(GetXOffscreenBits, 505)
    --x;
    y = M(Enemy_SprDataOffset + x);
    a <<= 1;
    pha();
    if (!c)
        goto SChk2;
    a = 0xf8;
    writeData(Sprite_Y_Position + y, a);
SChk2:
    pla();
    a <<= 1;
    pha();
    if (!c)
        goto SChk3;
    a = 0xf8;
    writeData(Sprite_Y_Position + 4 + y, a);
SChk3:
    pla();
    a <<= 1;
    pha();
    if (!c)
        goto SChk4;
    a = 0xf8;
    writeData(Sprite_Y_Position + 8 + y, a);
SChk4:
    pla();
    a <<= 1;
    pha();
    if (!c)
        goto SChk5;
    a = 0xf8;
    writeData(Sprite_Y_Position + 12 + y, a);
SChk5:
    pla();
    a <<= 1;
    pha();
    if (!c)
        goto SChk6;
    a = 0xf8;
    writeData(Sprite_Y_Position + 16 + y, a);
SChk6:
    pla();
    a <<= 1;
    if (!c)
        goto SLChk;
    a = 0xf8;
    writeData(Sprite_Y_Position + 20 + y, a);
SLChk:
    a = M(Enemy_OffscreenBits);
    a <<= 1;
    if (!c)
        goto ExDLPl;
    JSR(MoveSixSpritesOffscreen, 506)
ExDLPl:
    goto Return;

//---------------------------------------------------------------------

DrawFloateyNumber_Coin:
    a = M(FrameCounter);
    a >>= 1;
    if (c)
        goto NotRsNum;
    --M(Misc_Y_Position + x);
NotRsNum:
    a = M(Misc_Y_Position + x);
    JSR(DumpTwoSpr, 507)
    a = M(Misc_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 4 + y, a);
    a = 0x02;
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    a = 0xf7;
    writeData(Sprite_Tilenumber + y, a);
    a = 0xfb;
    writeData(Sprite_Tilenumber + 4 + y, a);
    goto ExJCGfx;
JCoinGfxHandler:
    y = M(Misc_SprDataOffset + x);
    a = M(Misc_State + x);
    compare(a, 0x02);
    if (c)
        goto DrawFloateyNumber_Coin;
    a = M(Misc_Y_Position + x);
    writeData(Sprite_Y_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_Y_Position + 4 + y, a);
    a = M(Misc_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    writeData(Sprite_X_Position + 4 + y, a);
    a = M(FrameCounter);
    a >>= 1;
    a &= BOOST_BINARY(00000011);
    x = a;
    a = M(JumpingCoinTiles + x);
    ++y;
    JSR(DumpTwoSpr, 508)
    --y;
    a = 0x02;
    writeData(Sprite_Attributes + y, a);
    a = 0x82;
    writeData(Sprite_Attributes + 4 + y, a);
    x = M(ObjectOffset);
ExJCGfx:
    goto Return;

//---------------------------------------------------------------------

DrawPowerUp:
    y = M(Enemy_SprDataOffset + 5);
    a = M(Enemy_Rel_YPos);
    c = 0;
    a += 0x08;
    writeData(0x02, a);
    a = M(Enemy_Rel_XPos);
    writeData(0x05, a);
    x = M(PowerUpType);
    a = M(PowerUpAttributes + x);
    a |= M(Enemy_SprAttrib + 5);
    writeData(0x04, a);
    a = x;
    pha();
    a <<= 1;
    a <<= 1;
    x = a;
    a = 0x01;
    writeData(0x07, a);
    writeData(0x03, a);
PUpDrawLoop:
    a = M(PowerUpGfxTable + x);
    writeData(0x00, a);
    a = M(PowerUpGfxTable + 1 + x);
    JSR(DrawOneSpriteRow, 509)
    --M(0x07);
    if (!n)
        goto PUpDrawLoop;
    y = M(Enemy_SprDataOffset + 5);
    pla();
    if (z)
        goto PUpOfs;
    compare(a, 0x03);
    if (z)
        goto PUpOfs;
    writeData(0x00, a);
    a = M(FrameCounter);
    a >>= 1;
    a &= BOOST_BINARY(00000011);
    a |= M(Enemy_SprAttrib + 5);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    x = M(0x00);
    --x;
    if (z)
        goto FlipPUpRightSide;
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 12 + y, a);
FlipPUpRightSide:
    a = M(Sprite_Attributes + 4 + y);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 4 + y, a);
    a = M(Sprite_Attributes + 12 + y);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 12 + y, a);
PUpOfs:
    goto SprObjectOffscrChk;
EnemyGfxHandler:
    a = M(Enemy_Y_Position + x);
    writeData(0x02, a);
    a = M(Enemy_Rel_XPos);
    writeData(0x05, a);
    y = M(Enemy_SprDataOffset + x);
    writeData(0xeb, y);
    a = 0x00;
    writeData(VerticalFlipFlag, a);
    a = M(Enemy_MovingDir + x);
    writeData(0x03, a);
    a = M(Enemy_SprAttrib + x);
    writeData(0x04, a);
    a = M(Enemy_ID + x);
    compare(a, PiranhaPlant);
    if (!z)
        goto CheckForRetainerObj;
    y = M(PiranhaPlant_Y_Speed + x);
    if (n)
        goto CheckForRetainerObj;
    y = M(EnemyFrameTimer + x);
    if (z)
        goto CheckForRetainerObj;
    goto Return;

//---------------------------------------------------------------------

CheckForRetainerObj:
    a = M(Enemy_State + x);
    writeData(0xed, a);
    a &= BOOST_BINARY(00011111);
    y = a;
    a = M(Enemy_ID + x);
    compare(a, RetainerObject);
    if (!z)
        goto CheckForBulletBillCV;
    y = 0x00;
    a = 0x01;
    writeData(0x03, a);
    a = 0x15;
CheckForBulletBillCV:
    compare(a, BulletBill_CannonVar);
    if (!z)
        goto CheckForJumpspring;
    --M(0x02);
    a = 0x03;
    y = M(EnemyFrameTimer + x);
    if (z)
        goto SBBAt;
    a |= BOOST_BINARY(00100000);
SBBAt:
    writeData(0x04, a);
    y = 0x00;
    writeData(0xed, y);
    a = 0x08;
CheckForJumpspring:
    compare(a, JumpspringObject);
    if (!z)
        goto CheckForPodoboo;
    y = 0x03;
    x = M(JumpspringAnimCtrl);
    a = M(JumpspringFrameOffsets + x);
CheckForPodoboo:
    writeData(0xef, a);
    writeData(0xec, y);
    x = M(ObjectOffset);
    compare(a, 0x0c);
    if (!z)
        goto CheckBowserGfxFlag;
    a = M(Enemy_Y_Speed + x);
    if (n)
        goto CheckBowserGfxFlag;
    ++M(VerticalFlipFlag);
CheckBowserGfxFlag:
    a = M(BowserGfxFlag);
    if (z)
        goto CheckForGoomba;
    y = 0x16;
    compare(a, 0x01);
    if (z)
        goto SBwsrGfxOfs;
    ++y;
SBwsrGfxOfs:
    writeData(0xef, y);
CheckForGoomba:
    y = M(0xef);
    compare(y, Goomba);
    if (!z)
        goto CheckBowserFront;
    a = M(Enemy_State + x);
    compare(a, 0x02);
    if (!c)
        goto GmbaAnim;
    x = 0x04;
    writeData(0xec, x);
GmbaAnim:
    a &= BOOST_BINARY(00100000);
    a |= M(TimerControl);
    if (!z)
        goto CheckBowserFront;
    a = M(FrameCounter);
    a &= BOOST_BINARY(00001000);
    if (!z)
        goto CheckBowserFront;
    a = M(0x03);
    a ^= BOOST_BINARY(00000011);
    writeData(0x03, a);
CheckBowserFront:
    a = M(EnemyAttributeData + y);
    a |= M(0x04);
    writeData(0x04, a);
    a = M(EnemyGfxTableOffsets + y);
    x = a;
    y = M(0xec);
    a = M(BowserGfxFlag);
    if (z)
        goto CheckForSpiny;
    compare(a, 0x01);
    if (!z)
        goto CheckBowserRear;
    a = M(BowserBodyControls);
    if (!n)
        goto ChkFrontSte;
    x = 0xde;
ChkFrontSte:
    a = M(0xed);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto DrawBowser;
FlipBowserOver:
    writeData(VerticalFlipFlag, x);
DrawBowser:
    goto DrawEnemyObject;
CheckBowserRear:
    a = M(BowserBodyControls);
    a &= 0x01;
    if (z)
        goto ChkRearSte;
    x = 0xe4;
ChkRearSte:
    a = M(0xed);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto DrawBowser;
    a = M(0x02);
    c = 1;
    a -= 0x10;
    writeData(0x02, a);
    goto FlipBowserOver;
CheckForSpiny:
    compare(x, 0x24);
    if (!z)
        goto CheckForLakitu;
    compare(y, 0x05);
    if (!z)
        goto NotEgg;
    x = 0x30;
    a = 0x02;
    writeData(0x03, a);
    a = 0x05;
    writeData(0xec, a);
NotEgg:
    goto CheckForHammerBro;
CheckForLakitu:
    compare(x, 0x90);
    if (!z)
        goto CheckUpsideDownShell;
    a = M(0xed);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto NoLAFr;
    a = M(FrenzyEnemyTimer);
    compare(a, 0x10);
    if (c)
        goto NoLAFr;
    x = 0x96;
NoLAFr:
    goto CheckDefeatedState;
CheckUpsideDownShell:
    a = M(0xef);
    compare(a, 0x04);
    if (c)
        goto CheckRightSideUpShell;
    compare(y, 0x02);
    if (!c)
        goto CheckRightSideUpShell;
    x = 0x5a;
    y = M(0xef);
    compare(y, BuzzyBeetle);
    if (!z)
        goto CheckRightSideUpShell;
    x = 0x7e;
    ++M(0x02);
CheckRightSideUpShell:
    a = M(0xec);
    compare(a, 0x04);
    if (!z)
        goto CheckForHammerBro;
    x = 0x72;
    ++M(0x02);
    y = M(0xef);
    compare(y, BuzzyBeetle);
    if (z)
        goto CheckForDefdGoomba;
    x = 0x66;
    ++M(0x02);
CheckForDefdGoomba:
    compare(y, Goomba);
    if (!z)
        goto CheckForHammerBro;
    x = 0x54;
    a = M(0xed);
    a &= BOOST_BINARY(00100000);
    if (!z)
        goto CheckForHammerBro;
    x = 0x8a;
    --M(0x02);
CheckForHammerBro:
    y = M(ObjectOffset);
    a = M(0xef);
    compare(a, HammerBro);
    if (!z)
        goto CheckForBloober;
    a = M(0xed);
    if (z)
        goto CheckToAnimateEnemy;
    a &= BOOST_BINARY(00001000);
    if (z)
        goto CheckDefeatedState;
    x = 0xb4;
    if (!z)
        goto CheckToAnimateEnemy;
CheckForBloober:
    compare(x, 0x48);
    if (z)
        goto CheckToAnimateEnemy;
    a = M(EnemyIntervalTimer + y);
    compare(a, 0x05);
    if (c)
        goto CheckDefeatedState;
    compare(x, 0x3c);
    if (!z)
        goto CheckToAnimateEnemy;
    compare(a, 0x01);
    if (z)
        goto CheckDefeatedState;
    ++M(0x02);
    ++M(0x02);
    ++M(0x02);
    goto CheckAnimationStop;
CheckToAnimateEnemy:
    a = M(0xef);
    compare(a, Goomba);
    if (z)
        goto CheckDefeatedState;
    compare(a, 0x08);
    if (z)
        goto CheckDefeatedState;
    compare(a, Podoboo);
    if (z)
        goto CheckDefeatedState;
    compare(a, 0x18);
    if (c)
        goto CheckDefeatedState;
    y = 0x00;
    compare(a, 0x15);
    if (!z)
        goto CheckForSecondFrame;
    ++y;
    a = M(WorldNumber);
    compare(a, World8);
    if (c)
        goto CheckDefeatedState;
    x = 0xa2;
    a = 0x03;
    writeData(0xec, a);
    if (!z)
        goto CheckDefeatedState;
CheckForSecondFrame:
    a = M(FrameCounter);
    a &= M(EnemyAnimTimingBMask + y);
    if (!z)
        goto CheckDefeatedState;
CheckAnimationStop:
    a = M(0xed);
    a &= BOOST_BINARY(10100000);
    a |= M(TimerControl);
    if (!z)
        goto CheckDefeatedState;
    a = x;
    c = 0;
    a += 0x06;
    x = a;
CheckDefeatedState:
    a = M(0xed);
    a &= BOOST_BINARY(00100000);
    if (z)
        goto DrawEnemyObject;
    a = M(0xef);
    compare(a, 0x04);
    if (!c)
        goto DrawEnemyObject;
    y = 0x01;
    writeData(VerticalFlipFlag, y);
    --y;
    writeData(0xec, y);
DrawEnemyObject:
    y = M(0xeb);
    JSR(DrawEnemyObjRow, 510)
    JSR(DrawEnemyObjRow, 511)
    JSR(DrawEnemyObjRow, 512)
    x = M(ObjectOffset);
    y = M(Enemy_SprDataOffset + x);
    a = M(0xef);
    compare(a, 0x08);
    if (!z)
        goto CheckForVerticalFlip;
SkipToOffScrChk:
    goto SprObjectOffscrChk;
CheckForVerticalFlip:
    a = M(VerticalFlipFlag);
    if (z)
        goto CheckForESymmetry;
    a = M(Sprite_Attributes + y);
    a |= BOOST_BINARY(10000000);
    ++y;
    ++y;
    JSR(DumpSixSpr, 513)
    --y;
    --y;
    a = y;
    x = a;
    a = M(0xef);
    compare(a, HammerBro);
    if (z)
        goto FlipEnemyVertically;
    compare(a, Lakitu);
    if (z)
        goto FlipEnemyVertically;
    compare(a, 0x15);
    if (c)
        goto FlipEnemyVertically;
    a = x;
    c = 0;
    a += 0x08;
    x = a;
FlipEnemyVertically:
    a = M(Sprite_Tilenumber + x);
    pha();
    a = M(Sprite_Tilenumber + 4 + x);
    pha();
    a = M(Sprite_Tilenumber + 16 + y);
    writeData(Sprite_Tilenumber + x, a);
    a = M(Sprite_Tilenumber + 20 + y);
    writeData(Sprite_Tilenumber + 4 + x, a);
    pla();
    writeData(Sprite_Tilenumber + 20 + y, a);
    pla();
    writeData(Sprite_Tilenumber + 16 + y, a);
CheckForESymmetry:
    a = M(BowserGfxFlag);
    if (!z)
        goto SkipToOffScrChk;
    a = M(0xef);
    x = M(0xec);
    compare(a, 0x05);
    if (!z)
        goto ContES;
    goto SprObjectOffscrChk;
ContES:
    compare(a, Bloober);
    if (z)
        goto MirrorEnemyGfx;
    compare(a, PiranhaPlant);
    if (z)
        goto MirrorEnemyGfx;
    compare(a, Podoboo);
    if (z)
        goto MirrorEnemyGfx;
    compare(a, Spiny);
    if (!z)
        goto ESRtnr;
    compare(x, 0x05);
    if (!z)
        goto CheckToMirrorLakitu;
ESRtnr:
    compare(a, 0x15);
    if (!z)
        goto SpnySC;
    a = 0x42;
    writeData(Sprite_Attributes + 20 + y, a);
SpnySC:
    compare(x, 0x02);
    if (!c)
        goto CheckToMirrorLakitu;
MirrorEnemyGfx:
    a = M(BowserGfxFlag);
    if (!z)
        goto CheckToMirrorLakitu;
    a = M(Sprite_Attributes + y);
    a &= BOOST_BINARY(10100011);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 16 + y, a);
    a |= BOOST_BINARY(01000000);
    compare(x, 0x05);
    if (!z)
        goto EggExc;
    a |= BOOST_BINARY(10000000);
EggExc:
    writeData(Sprite_Attributes + 4 + y, a);
    writeData(Sprite_Attributes + 12 + y, a);
    writeData(Sprite_Attributes + 20 + y, a);
    compare(x, 0x04);
    if (!z)
        goto CheckToMirrorLakitu;
    a = M(Sprite_Attributes + 8 + y);
    a |= BOOST_BINARY(10000000);
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 16 + y, a);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 12 + y, a);
    writeData(Sprite_Attributes + 20 + y, a);
CheckToMirrorLakitu:
    a = M(0xef);
    compare(a, Lakitu);
    if (!z)
        goto CheckToMirrorJSpring;
    a = M(VerticalFlipFlag);
    if (!z)
        goto NVFLak;
    a = M(Sprite_Attributes + 16 + y);
    a &= BOOST_BINARY(10000001);
    writeData(Sprite_Attributes + 16 + y, a);
    a = M(Sprite_Attributes + 20 + y);
    a |= BOOST_BINARY(01000001);
    writeData(Sprite_Attributes + 20 + y, a);
    x = M(FrenzyEnemyTimer);
    compare(x, 0x10);
    if (c)
        goto SprObjectOffscrChk;
    writeData(Sprite_Attributes + 12 + y, a);
    a &= BOOST_BINARY(10000001);
    writeData(Sprite_Attributes + 8 + y, a);
    if (!c)
        goto SprObjectOffscrChk;
NVFLak:
    a = M(Sprite_Attributes + y);
    a &= BOOST_BINARY(10000001);
    writeData(Sprite_Attributes + y, a);
    a = M(Sprite_Attributes + 4 + y);
    a |= BOOST_BINARY(01000001);
    writeData(Sprite_Attributes + 4 + y, a);
CheckToMirrorJSpring:
    a = M(0xef);
    compare(a, 0x18);
    if (!c)
        goto SprObjectOffscrChk;
    a = 0x82;
    writeData(Sprite_Attributes + 8 + y, a);
    writeData(Sprite_Attributes + 16 + y, a);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 12 + y, a);
    writeData(Sprite_Attributes + 20 + y, a);
SprObjectOffscrChk:
    x = M(ObjectOffset);
    a = M(Enemy_OffscreenBits);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    pha();
    if (!c)
        goto LcChk;
    a = 0x04;
    JSR(MoveESprColOffscreen, 514)
LcChk:
    pla();
    a >>= 1;
    pha();
    if (!c)
        goto Row3C;
    a = 0x00;
    JSR(MoveESprColOffscreen, 515)
Row3C:
    pla();
    a >>= 1;
    a >>= 1;
    pha();
    if (!c)
        goto Row23C;
    a = 0x10;
    JSR(MoveESprRowOffscreen, 516)
Row23C:
    pla();
    a >>= 1;
    pha();
    if (!c)
        goto AllRowC;
    a = 0x08;
    JSR(MoveESprRowOffscreen, 517)
AllRowC:
    pla();
    a >>= 1;
    if (!c)
        goto ExEGHandler;
    JSR(MoveESprRowOffscreen, 518)
    a = M(Enemy_ID + x);
    compare(a, Podoboo);
    if (z)
        goto ExEGHandler;
    a = M(Enemy_Y_HighPos + x);
    compare(a, 0x02);
    if (!z)
        goto ExEGHandler;
    JSR(EraseEnemyObject, 519)
ExEGHandler:
    goto Return;

//---------------------------------------------------------------------

DrawEnemyObjRow:
    a = M(EnemyGraphicsTable + x);
    writeData(0x00, a);
    a = M(EnemyGraphicsTable + 1 + x);
DrawOneSpriteRow:
    writeData(0x01, a);
    goto DrawSpriteObject;
MoveESprRowOffscreen:
    c = 0;
    a += M(Enemy_SprDataOffset + x);
    y = a;
    a = 0xf8;
    goto DumpTwoSpr;
MoveESprColOffscreen:
    c = 0;
    a += M(Enemy_SprDataOffset + x);
    y = a;
    JSR(MoveColOffscreen, 520)
    writeData(Sprite_Data + 16 + y, a);
    goto Return;

//---------------------------------------------------------------------

DrawBlock:
    a = M(Block_Rel_YPos);
    writeData(0x02, a);
    a = M(Block_Rel_XPos);
    writeData(0x05, a);
    a = 0x03;
    writeData(0x04, a);
    a >>= 1;
    writeData(0x03, a);
    y = M(Block_SprDataOffset + x);
    x = 0x00;
DBlkLoop:
    a = M(DefaultBlockObjTiles + x);
    writeData(0x00, a);
    a = M(DefaultBlockObjTiles + 1 + x);
    JSR(DrawOneSpriteRow, 521)
    compare(x, 0x04);
    if (!z)
        goto DBlkLoop;
    x = M(ObjectOffset);
    y = M(Block_SprDataOffset + x);
    a = M(AreaType);
    compare(a, 0x01);
    if (z)
        goto ChkRep;
    a = 0x86;
    writeData(Sprite_Tilenumber + y, a);
    writeData(Sprite_Tilenumber + 4 + y, a);
ChkRep:
    a = M(Block_Metatile + x);
    compare(a, 0xc4);
    if (!z)
        goto BlkOffscr;
    a = 0x87;
    ++y;
    JSR(DumpFourSpr, 522)
    --y;
    a = 0x03;
    x = M(AreaType);
    --x;
    if (z)
        goto SetBFlip;
    a >>= 1;
SetBFlip:
    x = M(ObjectOffset);
    writeData(Sprite_Attributes + y, a);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 4 + y, a);
    a |= BOOST_BINARY(10000000);
    writeData(Sprite_Attributes + 12 + y, a);
    a &= BOOST_BINARY(10000011);
    writeData(Sprite_Attributes + 8 + y, a);
BlkOffscr:
    a = M(Block_OffscreenBits);
    pha();
    a &= BOOST_BINARY(00000100);
    if (z)
        goto PullOfsB;
    a = 0xf8;
    writeData(Sprite_Y_Position + 4 + y, a);
    writeData(Sprite_Y_Position + 12 + y, a);
PullOfsB:
    pla();
ChkLeftCo:
    a &= BOOST_BINARY(00001000);
    if (z)
        goto ExDBlk;
MoveColOffscreen:
    a = 0xf8;
    writeData(Sprite_Y_Position + y, a);
    writeData(Sprite_Y_Position + 8 + y, a);
ExDBlk:
    goto Return;

//---------------------------------------------------------------------

DrawBrickChunks:
    a = 0x02;
    writeData(0x00, a);
    a = 0x75;
    y = M(GameEngineSubroutine);
    compare(y, 0x05);
    if (z)
        goto DChunks;
    a = 0x03;
    writeData(0x00, a);
    a = 0x84;
DChunks:
    y = M(Block_SprDataOffset + x);
    ++y;
    JSR(DumpFourSpr, 523)
    a = M(FrameCounter);
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a &= 0xc0;
    a |= M(0x00);
    ++y;
    JSR(DumpFourSpr, 524)
    --y;
    --y;
    a = M(Block_Rel_YPos);
    JSR(DumpTwoSpr, 525)
    a = M(Block_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    a = M(Block_Orig_XPos + x);
    c = 1;
    a -= M(ScreenLeft_X_Pos);
    writeData(0x00, a);
    c = 1;
    a -= M(Block_Rel_XPos);
    a += M(0x00);
    a += 0x06;
    writeData(Sprite_X_Position + 4 + y, a);
    a = M(Block_Rel_YPos + 1);
    writeData(Sprite_Y_Position + 8 + y, a);
    writeData(Sprite_Y_Position + 12 + y, a);
    a = M(Block_Rel_XPos + 1);
    writeData(Sprite_X_Position + 8 + y, a);
    a = M(0x00);
    c = 1;
    a -= M(Block_Rel_XPos + 1);
    a += M(0x00);
    a += 0x06;
    writeData(Sprite_X_Position + 12 + y, a);
    a = M(Block_OffscreenBits);
    JSR(ChkLeftCo, 526)
    a = M(Block_OffscreenBits);
    a <<= 1;
    if (!c)
        goto ChnkOfs;
    a = 0xf8;
    JSR(DumpTwoSpr, 527)
ChnkOfs:
    a = M(0x00);
    if (!n)
        goto ExBCDr;
    a = M(Sprite_X_Position + y);
    compare(a, M(Sprite_X_Position + 4 + y));
    if (!c)
        goto ExBCDr;
    a = 0xf8;
    writeData(Sprite_Y_Position + 4 + y, a);
    writeData(Sprite_Y_Position + 12 + y, a);
ExBCDr:
    goto Return;

//---------------------------------------------------------------------

DrawFireball:
    y = M(FBall_SprDataOffset + x);
    a = M(Fireball_Rel_YPos);
    writeData(Sprite_Y_Position + y, a);
    a = M(Fireball_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
DrawFirebar:
    a = M(FrameCounter);
    a >>= 1;
    a >>= 1;
    pha();
    a &= 0x01;
    a ^= 0x64;
    writeData(Sprite_Tilenumber + y, a);
    pla();
    a >>= 1;
    a >>= 1;
    a = 0x02;
    if (!c)
        goto FireA;
    a |= BOOST_BINARY(11000000);
FireA:
    writeData(Sprite_Attributes + y, a);
    goto Return;

//---------------------------------------------------------------------

DrawExplosion_Fireball:
    y = M(Alt_SprDataOffset + x);
    a = M(Fireball_State + x);
    ++M(Fireball_State + x);
    a >>= 1;
    a &= BOOST_BINARY(00000111);
    compare(a, 0x03);
    if (c)
        goto KillFireBall;
DrawExplosion_Fireworks:
    x = a;
    a = M(ExplosionTiles + x);
    ++y;
    JSR(DumpFourSpr, 528)
    --y;
    x = M(ObjectOffset);
    a = M(Fireball_Rel_YPos);
    c = 1;
    a -= 0x04;
    writeData(Sprite_Y_Position + y, a);
    writeData(Sprite_Y_Position + 8 + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_Y_Position + 4 + y, a);
    writeData(Sprite_Y_Position + 12 + y, a);
    a = M(Fireball_Rel_XPos);
    c = 1;
    a -= 0x04;
    writeData(Sprite_X_Position + y, a);
    writeData(Sprite_X_Position + 4 + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 8 + y, a);
    writeData(Sprite_X_Position + 12 + y, a);
    a = 0x02;
    writeData(Sprite_Attributes + y, a);
    a = 0x82;
    writeData(Sprite_Attributes + 4 + y, a);
    a = 0x42;
    writeData(Sprite_Attributes + 8 + y, a);
    a = 0xc2;
    writeData(Sprite_Attributes + 12 + y, a);
    goto Return;

//---------------------------------------------------------------------

KillFireBall:
    a = 0x00;
    writeData(Fireball_State + x, a);
    goto Return;

//---------------------------------------------------------------------

DrawSmallPlatform:
    y = M(Enemy_SprDataOffset + x);
    a = 0x5b;
    ++y;
    JSR(DumpSixSpr, 529)
    ++y;
    a = 0x02;
    JSR(DumpSixSpr, 530)
    --y;
    --y;
    a = M(Enemy_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    writeData(Sprite_X_Position + 12 + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 4 + y, a);
    writeData(Sprite_X_Position + 16 + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 8 + y, a);
    writeData(Sprite_X_Position + 20 + y, a);
    a = M(Enemy_Y_Position + x);
    x = a;
    pha();
    compare(x, 0x20);
    if (c)
        goto TopSP;
    a = 0xf8;
TopSP:
    JSR(DumpThreeSpr, 531)
    pla();
    c = 0;
    a += 0x80;
    x = a;
    compare(x, 0x20);
    if (c)
        goto BotSP;
    a = 0xf8;
BotSP:
    writeData(Sprite_Y_Position + 12 + y, a);
    writeData(Sprite_Y_Position + 16 + y, a);
    writeData(Sprite_Y_Position + 20 + y, a);
    a = M(Enemy_OffscreenBits);
    pha();
    a &= BOOST_BINARY(00001000);
    if (z)
        goto SOfs;
    a = 0xf8;
    writeData(Sprite_Y_Position + y, a);
    writeData(Sprite_Y_Position + 12 + y, a);
SOfs:
    pla();
    pha();
    a &= BOOST_BINARY(00000100);
    if (z)
        goto SOfs2;
    a = 0xf8;
    writeData(Sprite_Y_Position + 4 + y, a);
    writeData(Sprite_Y_Position + 16 + y, a);
SOfs2:
    pla();
    a &= BOOST_BINARY(00000010);
    if (z)
        goto ExSPl;
    a = 0xf8;
    writeData(Sprite_Y_Position + 8 + y, a);
    writeData(Sprite_Y_Position + 20 + y, a);
ExSPl:
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

DrawBubble:
    y = M(Player_Y_HighPos);
    --y;
    if (!z)
        goto ExDBub;
    a = M(Bubble_OffscreenBits);
    a &= BOOST_BINARY(00001000);
    if (!z)
        goto ExDBub;
    y = M(Bubble_SprDataOffset + x);
    a = M(Bubble_Rel_XPos);
    writeData(Sprite_X_Position + y, a);
    a = M(Bubble_Rel_YPos);
    writeData(Sprite_Y_Position + y, a);
    a = 0x74;
    writeData(Sprite_Tilenumber + y, a);
    a = 0x02;
    writeData(Sprite_Attributes + y, a);
ExDBub:
    goto Return;

//---------------------------------------------------------------------

PlayerGfxHandler:
    a = M(InjuryTimer);
    if (z)
        goto CntPl;
    a = M(FrameCounter);
    a >>= 1;
    if (c)
        goto ExPGH;
CntPl:
    a = M(GameEngineSubroutine);
    compare(a, 0x0b);
    if (z)
        goto PlayerKilled;
    a = M(PlayerChangeSizeFlag);
    if (!z)
        goto DoChangeSize;
    y = M(SwimmingFlag);
    if (z)
        goto FindPlayerAction;
    a = M(Player_State);
    compare(a, 0x00);
    if (z)
        goto FindPlayerAction;
    JSR(FindPlayerAction, 532)
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000100);
    if (!z)
        goto ExPGH;
    x = a;
    y = M(Player_SprDataOffset);
    a = M(PlayerFacingDir);
    a >>= 1;
    if (c)
        goto SwimKT;
    ++y;
    ++y;
    ++y;
    ++y;
SwimKT:
    a = M(PlayerSize);
    if (z)
        goto BigKTS;
    a = M(Sprite_Tilenumber + 24 + y);
    compare(a, M(SwimTileRepOffset));
    if (z)
        goto ExPGH;
    ++x;
BigKTS:
    a = M(SwimKickTileNum + x);
    writeData(Sprite_Tilenumber + 24 + y, a);
ExPGH:
    goto Return;

//---------------------------------------------------------------------

FindPlayerAction:
    JSR(ProcessPlayerAction, 533)
    goto PlayerGfxProcessing;
DoChangeSize:
    JSR(HandleChangeSize, 534)
    goto PlayerGfxProcessing;
PlayerKilled:
    y = 0x0e;
    a = M(PlayerGfxTblOffsets + y);
PlayerGfxProcessing:
    writeData(PlayerGfxOffset, a);
    a = 0x04;
    JSR(RenderPlayerSub, 535)
    JSR(ChkForPlayerAttrib, 536)
    a = M(FireballThrowingTimer);
    if (z)
        goto PlayerOffscreenChk;
    y = 0x00;
    a = M(PlayerAnimTimer);
    compare(a, M(FireballThrowingTimer));
    writeData(FireballThrowingTimer, y);
    if (c)
        goto PlayerOffscreenChk;
    writeData(FireballThrowingTimer, a);
    y = 0x07;
    a = M(PlayerGfxTblOffsets + y);
    writeData(PlayerGfxOffset, a);
    y = 0x04;
    a = M(Player_X_Speed);
    a |= M(Left_Right_Buttons);
    if (z)
        goto SUpdR;
    --y;
SUpdR:
    a = y;
    JSR(RenderPlayerSub, 537)
PlayerOffscreenChk:
    a = M(Player_OffscreenBits);
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(0x00, a);
    x = 0x03;
    a = M(Player_SprDataOffset);
    c = 0;
    a += 0x18;
    y = a;
PROfsLoop:
    a = 0xf8;
    M(0x00) >>= 1;
    if (!c)
        goto NPROffscr;
    JSR(DumpTwoSpr, 538)
NPROffscr:
    a = y;
    c = 1;
    a -= 0x08;
    y = a;
    --x;
    if (!n)
        goto PROfsLoop;
    goto Return;

//---------------------------------------------------------------------

DrawPlayer_Intermediate:
    x = 0x05;
PIntLoop:
    a = M(IntermediatePlayerData + x);
    writeData(0x02 + x, a);
    --x;
    if (!n)
        goto PIntLoop;
    x = 0xb8;
    y = 0x04;
    JSR(DrawPlayerLoop, 539)
    a = M(Sprite_Attributes + 36);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 32, a);
    goto Return;

//---------------------------------------------------------------------

RenderPlayerSub:
    writeData(0x07, a);
    a = M(Player_Rel_XPos);
    writeData(Player_Pos_ForScroll, a);
    writeData(0x05, a);
    a = M(Player_Rel_YPos);
    writeData(0x02, a);
    a = M(PlayerFacingDir);
    writeData(0x03, a);
    a = M(Player_SprAttrib);
    writeData(0x04, a);
    x = M(PlayerGfxOffset);
    y = M(Player_SprDataOffset);
DrawPlayerLoop:
    a = M(PlayerGraphicsTable + x);
    writeData(0x00, a);
    a = M(PlayerGraphicsTable + 1 + x);
    JSR(DrawOneSpriteRow, 540)
    --M(0x07);
    if (!z)
        goto DrawPlayerLoop;
    goto Return;

//---------------------------------------------------------------------

ProcessPlayerAction:
    a = M(Player_State);
    compare(a, 0x03);
    if (z)
        goto ActionClimbing;
    compare(a, 0x02);
    if (z)
        goto ActionFalling;
    compare(a, 0x01);
    if (!z)
        goto ProcOnGroundActs;
    a = M(SwimmingFlag);
    if (!z)
        goto ActionSwimming;
    y = 0x06;
    a = M(CrouchingFlag);
    if (!z)
        goto NonAnimatedActs;
    y = 0x00;
    goto NonAnimatedActs;
ProcOnGroundActs:
    y = 0x06;
    a = M(CrouchingFlag);
    if (!z)
        goto NonAnimatedActs;
    y = 0x02;
    a = M(Player_X_Speed);
    a |= M(Left_Right_Buttons);
    if (z)
        goto NonAnimatedActs;
    a = M(Player_XSpeedAbsolute);
    compare(a, 0x09);
    if (!c)
        goto ActionWalkRun;
    a = M(Player_MovingDir);
    a &= M(PlayerFacingDir);
    if (!z)
        goto ActionWalkRun;
    ++y;
NonAnimatedActs:
    JSR(GetGfxOffsetAdder, 541)
    a = 0x00;
    writeData(PlayerAnimCtrl, a);
    a = M(PlayerGfxTblOffsets + y);
    goto Return;

//---------------------------------------------------------------------

ActionFalling:
    y = 0x04;
    JSR(GetGfxOffsetAdder, 542)
    goto GetCurrentAnimOffset;
ActionWalkRun:
    y = 0x04;
    JSR(GetGfxOffsetAdder, 543)
    goto FourFrameExtent;
ActionClimbing:
    y = 0x05;
    a = M(Player_Y_Speed);
    if (z)
        goto NonAnimatedActs;
    JSR(GetGfxOffsetAdder, 544)
    goto ThreeFrameExtent;
ActionSwimming:
    y = 0x01;
    JSR(GetGfxOffsetAdder, 545)
    a = M(JumpSwimTimer);
    a |= M(PlayerAnimCtrl);
    if (!z)
        goto FourFrameExtent;
    a = M(A_B_Buttons);
    a <<= 1;
    if (c)
        goto FourFrameExtent;
GetCurrentAnimOffset:
    a = M(PlayerAnimCtrl);
    goto GetOffsetFromAnimCtrl;
FourFrameExtent:
    a = 0x03;
    goto AnimationControl;
ThreeFrameExtent:
    a = 0x02;
AnimationControl:
    writeData(0x00, a);
    JSR(GetCurrentAnimOffset, 546)
    pha();
    a = M(PlayerAnimTimer);
    if (!z)
        goto ExAnimC;
    a = M(PlayerAnimTimerSet);
    writeData(PlayerAnimTimer, a);
    a = M(PlayerAnimCtrl);
    c = 0;
    a += 0x01;
    compare(a, M(0x00));
    if (!c)
        goto SetAnimC;
    a = 0x00;
SetAnimC:
    writeData(PlayerAnimCtrl, a);
ExAnimC:
    pla();
    goto Return;

//---------------------------------------------------------------------

GetGfxOffsetAdder:
    a = M(PlayerSize);
    if (z)
        goto SzOfs;
    a = y;
    c = 0;
    a += 0x08;
    y = a;
SzOfs:
    goto Return;

//---------------------------------------------------------------------

HandleChangeSize:
    y = M(PlayerAnimCtrl);
    a = M(FrameCounter);
    a &= BOOST_BINARY(00000011);
    if (!z)
        goto GorSLog;
    ++y;
    compare(y, 0x0a);
    if (!c)
        goto CSzNext;
    y = 0x00;
    writeData(PlayerChangeSizeFlag, y);
CSzNext:
    writeData(PlayerAnimCtrl, y);
GorSLog:
    a = M(PlayerSize);
    if (!z)
        goto ShrinkPlayer;
    a = M(ChangeSizeOffsetAdder + y);
    y = 0x0f;
GetOffsetFromAnimCtrl:
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a += M(PlayerGfxTblOffsets + y);
    goto Return;

//---------------------------------------------------------------------

ShrinkPlayer:
    a = y;
    c = 0;
    a += 0x0a;
    x = a;
    y = 0x09;
    a = M(ChangeSizeOffsetAdder + x);
    if (!z)
        goto ShrPlF;
    y = 0x01;
ShrPlF:
    a = M(PlayerGfxTblOffsets + y);
    goto Return;

//---------------------------------------------------------------------

ChkForPlayerAttrib:
    y = M(Player_SprDataOffset);
    a = M(GameEngineSubroutine);
    compare(a, 0x0b);
    if (z)
        goto KilledAtt;
    a = M(PlayerGfxOffset);
    compare(a, 0x50);
    if (z)
        goto C_S_IGAtt;
    compare(a, 0xb8);
    if (z)
        goto C_S_IGAtt;
    compare(a, 0xc0);
    if (z)
        goto C_S_IGAtt;
    compare(a, 0xc8);
    if (!z)
        goto ExPlyrAt;
KilledAtt:
    a = M(Sprite_Attributes + 16 + y);
    a &= BOOST_BINARY(00111111);
    writeData(Sprite_Attributes + 16 + y, a);
    a = M(Sprite_Attributes + 20 + y);
    a &= BOOST_BINARY(00111111);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 20 + y, a);
C_S_IGAtt:
    a = M(Sprite_Attributes + 24 + y);
    a &= BOOST_BINARY(00111111);
    writeData(Sprite_Attributes + 24 + y, a);
    a = M(Sprite_Attributes + 28 + y);
    a &= BOOST_BINARY(00111111);
    a |= BOOST_BINARY(01000000);
    writeData(Sprite_Attributes + 28 + y, a);
ExPlyrAt:
    goto Return;

//---------------------------------------------------------------------

RelativePlayerPosition:
    x = 0x00;
    y = 0x00;
    goto RelWOfs;
RelativeBubblePosition:
    y = 0x01;
    JSR(GetProperObjOffset, 547)
    y = 0x03;
    goto RelWOfs;
RelativeFireballPosition:
    y = 0x00;
    JSR(GetProperObjOffset, 548)
    y = 0x02;
RelWOfs:
    JSR(GetObjRelativePosition, 549)
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

RelativeMiscPosition:
    y = 0x02;
    JSR(GetProperObjOffset, 550)
    y = 0x06;
    goto RelWOfs;
RelativeEnemyPosition:
    a = 0x01;
    y = 0x01;
    goto VariableObjOfsRelPos;
RelativeBlockPosition:
    a = 0x09;
    y = 0x04;
    JSR(VariableObjOfsRelPos, 551)
    ++x;
    ++x;
    a = 0x09;
    ++y;
VariableObjOfsRelPos:
    writeData(0x00, x);
    c = 0;
    a += M(0x00);
    x = a;
    JSR(GetObjRelativePosition, 552)
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

GetObjRelativePosition:
    a = M(SprObject_Y_Position + x);
    writeData(SprObject_Rel_YPos + y, a);
    a = M(SprObject_X_Position + x);
    c = 1;
    a -= M(ScreenLeft_X_Pos);
    writeData(SprObject_Rel_XPos + y, a);
    goto Return;

//---------------------------------------------------------------------

GetPlayerOffscreenBits:
    x = 0x00;
    y = 0x00;
    goto GetOffScreenBitsSet;
GetFireballOffscreenBits:
    y = 0x00;
    JSR(GetProperObjOffset, 553)
    y = 0x02;
    goto GetOffScreenBitsSet;
GetBubbleOffscreenBits:
    y = 0x01;
    JSR(GetProperObjOffset, 554)
    y = 0x03;
    goto GetOffScreenBitsSet;
GetMiscOffscreenBits:
    y = 0x02;
    JSR(GetProperObjOffset, 555)
    y = 0x06;
    goto GetOffScreenBitsSet;
GetProperObjOffset:
    a = x;
    c = 0;
    a += M(ObjOffsetData + y);
    x = a;
    goto Return;

//---------------------------------------------------------------------

GetEnemyOffscreenBits:
    a = 0x01;
    y = 0x01;
    goto SetOffscrBitsOffset;
GetBlockOffscreenBits:
    a = 0x09;
    y = 0x04;
SetOffscrBitsOffset:
    writeData(0x00, x);
    c = 0;
    a += M(0x00);
    x = a;
GetOffScreenBitsSet:
    a = y;
    pha();
    JSR(RunOffscrBitsSubs, 556)
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a <<= 1;
    a |= M(0x00);
    writeData(0x00, a);
    pla();
    y = a;
    a = M(0x00);
    writeData(SprObject_OffscrBits + y, a);
    x = M(ObjectOffset);
    goto Return;

//---------------------------------------------------------------------

RunOffscrBitsSubs:
    JSR(GetXOffscreenBits, 557)
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    writeData(0x00, a);
    goto GetYOffscreenBits;
GetXOffscreenBits:
    writeData(0x04, x);
    y = 0x01;
XOfsLoop:
    a = M(ScreenEdge_X_Pos + y);
    c = 1;
    a -= M(SprObject_X_Position + x);
    writeData(0x07, a);
    a = M(ScreenEdge_PageLoc + y);
    a -= M(SprObject_PageLoc + x);
    x = M(DefaultXOnscreenOfs + y);
    compare(a, 0x00);
    if (n)
        goto XLdBData;
    x = M(DefaultXOnscreenOfs + 1 + y);
    compare(a, 0x01);
    if (!n)
        goto XLdBData;
    a = 0x38;
    writeData(0x06, a);
    a = 0x08;
    JSR(DividePDiff, 558)
XLdBData:
    a = M(XOffscreenBitsData + x);
    x = M(0x04);
    compare(a, 0x00);
    if (!z)
        goto ExXOfsBS;
    --y;
    if (!n)
        goto XOfsLoop;
ExXOfsBS:
    goto Return;

//---------------------------------------------------------------------

GetYOffscreenBits:
    writeData(0x04, x);
    y = 0x01;
YOfsLoop:
    a = M(HighPosUnitData + y);
    c = 1;
    a -= M(SprObject_Y_Position + x);
    writeData(0x07, a);
    a = 0x01;
    a -= M(SprObject_Y_HighPos + x);
    x = M(DefaultYOnscreenOfs + y);
    compare(a, 0x00);
    if (n)
        goto YLdBData;
    x = M(DefaultYOnscreenOfs + 1 + y);
    compare(a, 0x01);
    if (!n)
        goto YLdBData;
    a = 0x20;
    writeData(0x06, a);
    a = 0x04;
    JSR(DividePDiff, 559)
YLdBData:
    a = M(YOffscreenBitsData + x);
    x = M(0x04);
    compare(a, 0x00);
    if (!z)
        goto ExYOfsBS;
    --y;
    if (!n)
        goto YOfsLoop;
ExYOfsBS:
    goto Return;

//---------------------------------------------------------------------

DividePDiff:
    writeData(0x05, a);
    a = M(0x07);
    compare(a, M(0x06));
    if (c)
        goto ExDivPD;
    a >>= 1;
    a >>= 1;
    a >>= 1;
    a &= 0x07;
    compare(y, 0x01);
    if (c)
        goto SetOscrO;
    a += M(0x05);
SetOscrO:
    x = a;
ExDivPD:
    goto Return;

//---------------------------------------------------------------------

DrawSpriteObject:
    a = M(0x03);
    a >>= 1;
    a >>= 1;
    a = M(0x00);
    if (!c)
        goto NoHFlip;
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = M(0x01);
    writeData(Sprite_Tilenumber + y, a);
    a = 0x40;
    if (!z)
        goto SetHFAt;
NoHFlip:
    writeData(Sprite_Tilenumber + y, a);
    a = M(0x01);
    writeData(Sprite_Tilenumber + 4 + y, a);
    a = 0x00;
SetHFAt:
    a |= M(0x04);
    writeData(Sprite_Attributes + y, a);
    writeData(Sprite_Attributes + 4 + y, a);
    a = M(0x02);
    writeData(Sprite_Y_Position + y, a);
    writeData(Sprite_Y_Position + 4 + y, a);
    a = M(0x05);
    writeData(Sprite_X_Position + y, a);
    c = 0;
    a += 0x08;
    writeData(Sprite_X_Position + 4 + y, a);
    a = M(0x02);
    c = 0;
    a += 0x08;
    writeData(0x02, a);
    a = y;
    c = 0;
    a += 0x08;
    y = a;
    ++x;
    ++x;
    goto Return;

//---------------------------------------------------------------------

SoundEngine:
    a = M(OperMode);
    if (!z)
        goto SndOn;
    writeData(SND_MASTERCTRL_REG, a);
    goto Return;

//---------------------------------------------------------------------

SndOn:
    a = 0xff;
    writeData(JOYPAD_PORT2, a);
    a = 0x0f;
    writeData(SND_MASTERCTRL_REG, a);
    a = M(PauseModeFlag);
    if (!z)
        goto InPause;
    a = M(PauseSoundQueue);
    compare(a, 0x01);
    if (!z)
        goto RunSoundSubroutines;
InPause:
    a = M(PauseSoundBuffer);
    if (!z)
        goto ContPau;
    a = M(PauseSoundQueue);
    if (z)
        goto SkipSoundSubroutines;
    writeData(PauseSoundBuffer, a);
    writeData(PauseModeFlag, a);
    a = 0x00;
    writeData(SND_MASTERCTRL_REG, a);
    writeData(Square1SoundBuffer, a);
    writeData(Square2SoundBuffer, a);
    writeData(NoiseSoundBuffer, a);
    a = 0x0f;
    writeData(SND_MASTERCTRL_REG, a);
    a = 0x2a;
    writeData(Squ1_SfxLenCounter, a);
PTone1F:
    a = 0x44;
    if (!z)
        goto PTRegC;
ContPau:
    a = M(Squ1_SfxLenCounter);
    compare(a, 0x24);
    if (z)
        goto PTone2F;
    compare(a, 0x1e);
    if (z)
        goto PTone1F;
    compare(a, 0x18);
    if (!z)
        goto DecPauC;
PTone2F:
    a = 0x64;
PTRegC:
    x = 0x84;
    y = 0x7f;
    JSR(PlaySqu1Sfx, 560)
DecPauC:
    --M(Squ1_SfxLenCounter);
    if (!z)
        goto SkipSoundSubroutines;
    a = 0x00;
    writeData(SND_MASTERCTRL_REG, a);
    a = M(PauseSoundBuffer);
    compare(a, 0x02);
    if (!z)
        goto SkipPIn;
    a = 0x00;
    writeData(PauseModeFlag, a);
SkipPIn:
    a = 0x00;
    writeData(PauseSoundBuffer, a);
    if (z)
        goto SkipSoundSubroutines;
RunSoundSubroutines:
    JSR(Square1SfxHandler, 561)
    JSR(Square2SfxHandler, 562)
    JSR(NoiseSfxHandler, 563)
    JSR(MusicHandler, 564)
    a = 0x00;
    writeData(AreaMusicQueue, a);
    writeData(EventMusicQueue, a);
SkipSoundSubroutines:
    a = 0x00;
    writeData(Square1SoundQueue, a);
    writeData(Square2SoundQueue, a);
    writeData(NoiseSoundQueue, a);
    writeData(PauseSoundQueue, a);
    y = M(DAC_Counter);
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(00000011);
    if (z)
        goto NoIncDAC;
    ++M(DAC_Counter);
    compare(y, 0x30);
    if (!c)
        goto StrWave;
NoIncDAC:
    a = y;
    if (z)
        goto StrWave;
    --M(DAC_Counter);
StrWave:
    writeData(SND_DELTA_REG + 1, y);
    goto Return;

//---------------------------------------------------------------------

Dump_Squ1_Regs:
    writeData(SND_SQUARE1_REG + 1, y);
    writeData(SND_SQUARE1_REG, x);
    goto Return;

//---------------------------------------------------------------------

PlaySqu1Sfx:
    JSR(Dump_Squ1_Regs, 565)
SetFreq_Squ1:
    x = 0x00;
Dump_Freq_Regs:
    y = a;
    a = M(FreqRegLookupTbl + 1 + y);
    if (z)
        goto NoTone;
    writeData(SND_REGISTER + 2 + x, a);
    a = M(FreqRegLookupTbl + y);
    a |= BOOST_BINARY(00001000);
    writeData(SND_REGISTER + 3 + x, a);
NoTone:
    goto Return;

//---------------------------------------------------------------------

Dump_Sq2_Regs:
    writeData(SND_SQUARE2_REG, x);
    writeData(SND_SQUARE2_REG + 1, y);
    goto Return;

//---------------------------------------------------------------------

PlaySqu2Sfx:
    JSR(Dump_Sq2_Regs, 566)
SetFreq_Squ2:
    x = 0x04;
    if (!z)
        goto Dump_Freq_Regs;
SetFreq_Tri:
    x = 0x08;
    if (!z)
        goto Dump_Freq_Regs;
PlayFlagpoleSlide:
    a = 0x40;
    writeData(Squ1_SfxLenCounter, a);
    a = 0x62;
    JSR(SetFreq_Squ1, 567)
    x = 0x99;
    if (!z)
        goto FPS2nd;
PlaySmallJump:
    a = 0x26;
    if (!z)
        goto JumpRegContents;
PlayBigJump:
    a = 0x18;
JumpRegContents:
    x = 0x82;
    y = 0xa7;
    JSR(PlaySqu1Sfx, 568)
    a = 0x28;
    writeData(Squ1_SfxLenCounter, a);
ContinueSndJump:
    a = M(Squ1_SfxLenCounter);
    compare(a, 0x25);
    if (!z)
        goto N2Prt;
    x = 0x5f;
    y = 0xf6;
    if (!z)
        goto DmpJpFPS;
N2Prt:
    compare(a, 0x20);
    if (!z)
        goto DecJpFPS;
    x = 0x48;
FPS2nd:
    y = 0xbc;
DmpJpFPS:
    JSR(Dump_Squ1_Regs, 569)
    if (!z)
        goto DecJpFPS;
PlayFireballThrow:
    a = 0x05;
    y = 0x99;
    if (!z)
        goto Fthrow;
PlayBump:
    a = 0x0a;
    y = 0x93;
Fthrow:
    x = 0x9e;
    writeData(Squ1_SfxLenCounter, a);
    a = 0x0c;
    JSR(PlaySqu1Sfx, 570)
ContinueBumpThrow:
    a = M(Squ1_SfxLenCounter);
    compare(a, 0x06);
    if (!z)
        goto DecJpFPS;
    a = 0xbb;
    writeData(SND_SQUARE1_REG + 1, a);
DecJpFPS:
    if (!z)
        goto BranchToDecLength1;
Square1SfxHandler:
    y = M(Square1SoundQueue);
    if (z)
        goto CheckSfx1Buffer;
    writeData(Square1SoundBuffer, y);
    if (n)
        goto PlaySmallJump;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayBigJump;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayBump;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlaySwimStomp;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlaySmackEnemy;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayPipeDownInj;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayFireballThrow;
    M(Square1SoundQueue) >>= 1;
    if (c)
        goto PlayFlagpoleSlide;
CheckSfx1Buffer:
    a = M(Square1SoundBuffer);
    if (z)
        goto ExS1H;
    if (n)
        goto ContinueSndJump;
    a >>= 1;
    if (c)
        goto ContinueSndJump;
    a >>= 1;
    if (c)
        goto ContinueBumpThrow;
    a >>= 1;
    if (c)
        goto ContinueSwimStomp;
    a >>= 1;
    if (c)
        goto ContinueSmackEnemy;
    a >>= 1;
    if (c)
        goto ContinuePipeDownInj;
    a >>= 1;
    if (c)
        goto ContinueBumpThrow;
    a >>= 1;
    if (c)
        goto DecrementSfx1Length;
ExS1H:
    goto Return;

//---------------------------------------------------------------------

PlaySwimStomp:
    a = 0x0e;
    writeData(Squ1_SfxLenCounter, a);
    y = 0x9c;
    x = 0x9e;
    a = 0x26;
    JSR(PlaySqu1Sfx, 571)
ContinueSwimStomp:
    y = M(Squ1_SfxLenCounter);
    a = M(SwimStompEnvelopeData - 1 + y);
    writeData(SND_SQUARE1_REG, a);
    compare(y, 0x06);
    if (!z)
        goto BranchToDecLength1;
    a = 0x9e;
    writeData(SND_SQUARE1_REG + 2, a);
BranchToDecLength1:
    if (!z)
        goto DecrementSfx1Length;
PlaySmackEnemy:
    a = 0x0e;
    y = 0xcb;
    x = 0x9f;
    writeData(Squ1_SfxLenCounter, a);
    a = 0x28;
    JSR(PlaySqu1Sfx, 572)
    if (!z)
        goto DecrementSfx1Length;
ContinueSmackEnemy:
    y = M(Squ1_SfxLenCounter);
    compare(y, 0x08);
    if (!z)
        goto SmSpc;
    a = 0xa0;
    writeData(SND_SQUARE1_REG + 2, a);
    a = 0x9f;
    if (!z)
        goto SmTick;
SmSpc:
    a = 0x90;
SmTick:
    writeData(SND_SQUARE1_REG, a);
DecrementSfx1Length:
    --M(Squ1_SfxLenCounter);
    if (!z)
        goto ExSfx1;
StopSquare1Sfx:
    x = 0x00;
    writeData(0xf1, x);
    x = 0x0e;
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0f;
    writeData(SND_MASTERCTRL_REG, x);
ExSfx1:
    goto Return;

//---------------------------------------------------------------------

PlayPipeDownInj:
    a = 0x2f;
    writeData(Squ1_SfxLenCounter, a);
ContinuePipeDownInj:
    a = M(Squ1_SfxLenCounter);
    a >>= 1;
    if (c)
        goto NoPDwnL;
    a >>= 1;
    if (c)
        goto NoPDwnL;
    a &= BOOST_BINARY(00000010);
    if (z)
        goto NoPDwnL;
    y = 0x91;
    x = 0x9a;
    a = 0x44;
    JSR(PlaySqu1Sfx, 573)
NoPDwnL:
    goto DecrementSfx1Length;
PlayCoinGrab:
    a = 0x35;
    x = 0x8d;
    if (!z)
        goto CGrab_TTickRegL;
PlayTimerTick:
    a = 0x06;
    x = 0x98;
CGrab_TTickRegL:
    writeData(Squ2_SfxLenCounter, a);
    y = 0x7f;
    a = 0x42;
    JSR(PlaySqu2Sfx, 574)
ContinueCGrabTTick:
    a = M(Squ2_SfxLenCounter);
    compare(a, 0x30);
    if (!z)
        goto N2Tone;
    a = 0x54;
    writeData(SND_SQUARE2_REG + 2, a);
N2Tone:
    if (!z)
        goto DecrementSfx2Length;
PlayBlast:
    a = 0x20;
    writeData(Squ2_SfxLenCounter, a);
    y = 0x94;
    a = 0x5e;
    if (!z)
        goto SBlasJ;
ContinueBlast:
    a = M(Squ2_SfxLenCounter);
    compare(a, 0x18);
    if (!z)
        goto DecrementSfx2Length;
    y = 0x93;
    a = 0x18;
SBlasJ:
    if (!z)
        goto BlstSJp;
PlayPowerUpGrab:
    a = 0x36;
    writeData(Squ2_SfxLenCounter, a);
ContinuePowerUpGrab:
    a = M(Squ2_SfxLenCounter);
    a >>= 1;
    if (c)
        goto DecrementSfx2Length;
    y = a;
    a = M(PowerUpGrabFreqData - 1 + y);
    x = 0x5d;
    y = 0x7f;
LoadSqu2Regs:
    JSR(PlaySqu2Sfx, 575)
DecrementSfx2Length:
    --M(Squ2_SfxLenCounter);
    if (!z)
        goto ExSfx2;
EmptySfx2Buffer:
    x = 0x00;
    writeData(Square2SoundBuffer, x);
StopSquare2Sfx:
    x = 0x0d;
    writeData(SND_MASTERCTRL_REG, x);
    x = 0x0f;
    writeData(SND_MASTERCTRL_REG, x);
ExSfx2:
    goto Return;

//---------------------------------------------------------------------

Square2SfxHandler:
    a = M(Square2SoundBuffer);
    a &= Sfx_ExtraLife;
    if (!z)
        goto ContinueExtraLife;
    y = M(Square2SoundQueue);
    if (z)
        goto CheckSfx2Buffer;
    writeData(Square2SoundBuffer, y);
    if (n)
        goto PlayBowserFall;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayCoinGrab;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayGrowPowerUp;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayGrowVine;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayBlast;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayTimerTick;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayPowerUpGrab;
    M(Square2SoundQueue) >>= 1;
    if (c)
        goto PlayExtraLife;
CheckSfx2Buffer:
    a = M(Square2SoundBuffer);
    if (z)
        goto ExS2H;
    if (n)
        goto ContinueBowserFall;
    a >>= 1;
    if (c)
        goto Cont_CGrab_TTick;
    a >>= 1;
    if (c)
        goto ContinueGrowItems;
    a >>= 1;
    if (c)
        goto ContinueGrowItems;
    a >>= 1;
    if (c)
        goto ContinueBlast;
    a >>= 1;
    if (c)
        goto Cont_CGrab_TTick;
    a >>= 1;
    if (c)
        goto ContinuePowerUpGrab;
    a >>= 1;
    if (c)
        goto ContinueExtraLife;
ExS2H:
    goto Return;

//---------------------------------------------------------------------

Cont_CGrab_TTick:
    goto ContinueCGrabTTick;
JumpToDecLength2:
    goto DecrementSfx2Length;
PlayBowserFall:
    a = 0x38;
    writeData(Squ2_SfxLenCounter, a);
    y = 0xc4;
    a = 0x18;
BlstSJp:
    if (!z)
        goto PBFRegs;
ContinueBowserFall:
    a = M(Squ2_SfxLenCounter);
    compare(a, 0x08);
    if (!z)
        goto DecrementSfx2Length;
    y = 0xa4;
    a = 0x5a;
PBFRegs:
    x = 0x9f;
EL_LRegs:
    if (!z)
        goto LoadSqu2Regs;
PlayExtraLife:
    a = 0x30;
    writeData(Squ2_SfxLenCounter, a);
ContinueExtraLife:
    a = M(Squ2_SfxLenCounter);
    x = 0x03;
DivLLoop:
    a >>= 1;
    if (c)
        goto JumpToDecLength2;
    --x;
    if (!z)
        goto DivLLoop;
    y = a;
    a = M(ExtraLifeFreqData - 1 + y);
    x = 0x82;
    y = 0x7f;
    if (!z)
        goto EL_LRegs;
PlayGrowPowerUp:
    a = 0x10;
    if (!z)
        goto GrowItemRegs;
PlayGrowVine:
    a = 0x20;
GrowItemRegs:
    writeData(Squ2_SfxLenCounter, a);
    a = 0x7f;
    writeData(SND_SQUARE2_REG + 1, a);
    a = 0x00;
    writeData(Sfx_SecondaryCounter, a);
ContinueGrowItems:
    ++M(Sfx_SecondaryCounter);
    a = M(Sfx_SecondaryCounter);
    a >>= 1;
    y = a;
    compare(y, M(Squ2_SfxLenCounter));
    if (z)
        goto StopGrowItems;
    a = 0x9d;
    writeData(SND_SQUARE2_REG, a);
    a = M(PUp_VGrow_FreqData + y);
    JSR(SetFreq_Squ2, 576)
    goto Return;

//---------------------------------------------------------------------

StopGrowItems:
    goto EmptySfx2Buffer;
PlayBrickShatter:
    a = 0x20;
    writeData(Noise_SfxLenCounter, a);
ContinueBrickShatter:
    a = M(Noise_SfxLenCounter);
    a >>= 1;
    if (!c)
        goto DecrementSfx3Length;
    y = a;
    x = M(BrickShatterFreqData + y);
    a = M(BrickShatterEnvData + y);
PlayNoiseSfx:
    writeData(SND_NOISE_REG, a);
    writeData(SND_NOISE_REG + 2, x);
    a = 0x18;
    writeData(SND_NOISE_REG + 3, a);
DecrementSfx3Length:
    --M(Noise_SfxLenCounter);
    if (!z)
        goto ExSfx3;
    a = 0xf0;
    writeData(SND_NOISE_REG, a);
    a = 0x00;
    writeData(NoiseSoundBuffer, a);
ExSfx3:
    goto Return;

//---------------------------------------------------------------------

NoiseSfxHandler:
    y = M(NoiseSoundQueue);
    if (z)
        goto CheckNoiseBuffer;
    writeData(NoiseSoundBuffer, y);
    M(NoiseSoundQueue) >>= 1;
    if (c)
        goto PlayBrickShatter;
    M(NoiseSoundQueue) >>= 1;
    if (c)
        goto PlayBowserFlame;
CheckNoiseBuffer:
    a = M(NoiseSoundBuffer);
    if (z)
        goto ExNH;
    a >>= 1;
    if (c)
        goto ContinueBrickShatter;
    a >>= 1;
    if (c)
        goto ContinueBowserFlame;
ExNH:
    goto Return;

//---------------------------------------------------------------------

PlayBowserFlame:
    a = 0x40;
    writeData(Noise_SfxLenCounter, a);
ContinueBowserFlame:
    a = M(Noise_SfxLenCounter);
    a >>= 1;
    y = a;
    x = 0x0f;
    a = M(BowserFlameEnvData - 1 + y);
    if (!z)
        goto PlayNoiseSfx;
ContinueMusic:
    goto HandleSquare2Music;
MusicHandler:
    a = M(EventMusicQueue);
    if (!z)
        goto LoadEventMusic;
    a = M(AreaMusicQueue);
    if (!z)
        goto LoadAreaMusic;
    a = M(EventMusicBuffer);
    a |= M(AreaMusicBuffer);
    if (!z)
        goto ContinueMusic;
    goto Return;

//---------------------------------------------------------------------

LoadEventMusic:
    writeData(EventMusicBuffer, a);
    compare(a, DeathMusic);
    if (!z)
        goto NoStopSfx;
    JSR(StopSquare1Sfx, 577)
    JSR(StopSquare2Sfx, 578)
NoStopSfx:
    x = M(AreaMusicBuffer);
    writeData(AreaMusicBuffer_Alt, x);
    y = 0x00;
    writeData(NoteLengthTblAdder, y);
    writeData(AreaMusicBuffer, y);
    compare(a, TimeRunningOutMusic);
    if (!z)
        goto FindEventMusicHeader;
    x = 0x08;
    writeData(NoteLengthTblAdder, x);
    if (!z)
        goto FindEventMusicHeader;
LoadAreaMusic:
    compare(a, 0x04);
    if (!z)
        goto NoStop1;
    JSR(StopSquare1Sfx, 579)
NoStop1:
    y = 0x10;
GMLoopB:
    writeData(GroundMusicHeaderOfs, y);
HandleAreaMusicLoopB:
    y = 0x00;
    writeData(EventMusicBuffer, y);
    writeData(AreaMusicBuffer, a);
    compare(a, 0x01);
    if (!z)
        goto FindAreaMusicHeader;
    ++M(GroundMusicHeaderOfs);
    y = M(GroundMusicHeaderOfs);
    compare(y, 0x32);
    if (!z)
        goto LoadHeader;
    y = 0x11;
    if (!z)
        goto GMLoopB;
FindAreaMusicHeader:
    y = 0x08;
    writeData(MusicOffset_Square2, y);
FindEventMusicHeader:
    ++y;
    a >>= 1;
    if (!c)
        goto FindEventMusicHeader;
LoadHeader:
    a = M(MusicHeaderOffsetData + y);
    y = a;
    a = M(MusicHeaderData + y);
    writeData(NoteLenLookupTblOfs, a);
    a = M(MusicHeaderData + 1 + y);
    writeData(MusicDataLow, a);
    a = M(MusicHeaderData + 2 + y);
    writeData(MusicDataHigh, a);
    a = M(MusicHeaderData + 3 + y);
    writeData(MusicOffset_Triangle, a);
    a = M(MusicHeaderData + 4 + y);
    writeData(MusicOffset_Square1, a);
    a = M(MusicHeaderData + 5 + y);
    writeData(MusicOffset_Noise, a);
    writeData(NoiseDataLoopbackOfs, a);
    a = 0x01;
    writeData(Squ2_NoteLenCounter, a);
    writeData(Squ1_NoteLenCounter, a);
    writeData(Tri_NoteLenCounter, a);
    writeData(Noise_BeatLenCounter, a);
    a = 0x00;
    writeData(MusicOffset_Square2, a);
    writeData(AltRegContentFlag, a);
    a = 0x0b;
    writeData(SND_MASTERCTRL_REG, a);
    a = 0x0f;
    writeData(SND_MASTERCTRL_REG, a);
HandleSquare2Music:
    --M(Squ2_NoteLenCounter);
    if (!z)
        goto MiscSqu2MusicTasks;
    y = M(MusicOffset_Square2);
    ++M(MusicOffset_Square2);
    a = M(W(MusicData) + y);
    if (z)
        goto EndOfMusicData;
    if (!n)
        goto Squ2NoteHandler;
    if (!z)
        goto Squ2LengthHandler;
EndOfMusicData:
    a = M(EventMusicBuffer);
    compare(a, TimeRunningOutMusic);
    if (!z)
        goto NotTRO;
    a = M(AreaMusicBuffer_Alt);
    if (!z)
        goto MusicLoopBack;
NotTRO:
    a &= VictoryMusic;
    if (!z)
        goto VictoryMLoopBack;
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(01011111);
    if (!z)
        goto MusicLoopBack;
    a = 0x00;
    writeData(AreaMusicBuffer, a);
    writeData(EventMusicBuffer, a);
    writeData(SND_TRIANGLE_REG, a);
    a = 0x90;
    writeData(SND_SQUARE1_REG, a);
    writeData(SND_SQUARE2_REG, a);
    goto Return;

//---------------------------------------------------------------------

MusicLoopBack:
    goto HandleAreaMusicLoopB;
VictoryMLoopBack:
    goto LoadEventMusic;
Squ2LengthHandler:
    JSR(ProcessLengthData, 580)
    writeData(Squ2_NoteLenBuffer, a);
    y = M(MusicOffset_Square2);
    ++M(MusicOffset_Square2);
    a = M(W(MusicData) + y);
Squ2NoteHandler:
    x = M(Square2SoundBuffer);
    if (!z)
        goto SkipFqL1;
    JSR(SetFreq_Squ2, 581)
    if (z)
        goto Rest;
    JSR(LoadControlRegs, 582)
Rest:
    writeData(Squ2_EnvelopeDataCtrl, a);
    JSR(Dump_Sq2_Regs, 583)
SkipFqL1:
    a = M(Squ2_NoteLenBuffer);
    writeData(Squ2_NoteLenCounter, a);
MiscSqu2MusicTasks:
    a = M(Square2SoundBuffer);
    if (!z)
        goto HandleSquare1Music;
    a = M(EventMusicBuffer);
    a &= BOOST_BINARY(10010001);
    if (!z)
        goto HandleSquare1Music;
    y = M(Squ2_EnvelopeDataCtrl);
    if (z)
        goto NoDecEnv1;
    --M(Squ2_EnvelopeDataCtrl);
NoDecEnv1:
    JSR(LoadEnvelopeData, 584)
    writeData(SND_SQUARE2_REG, a);
    x = 0x7f;
    writeData(SND_SQUARE2_REG + 1, x);
HandleSquare1Music:
    y = M(MusicOffset_Square1);
    if (z)
        goto HandleTriangleMusic;
    --M(Squ1_NoteLenCounter);
    if (!z)
        goto MiscSqu1MusicTasks;
FetchSqu1MusicData:
    y = M(MusicOffset_Square1);
    ++M(MusicOffset_Square1);
    a = M(W(MusicData) + y);
    if (!z)
        goto Squ1NoteHandler;
    a = 0x83;
    writeData(SND_SQUARE1_REG, a);
    a = 0x94;
    writeData(SND_SQUARE1_REG + 1, a);
    writeData(AltRegContentFlag, a);
    if (!z)
        goto FetchSqu1MusicData;
Squ1NoteHandler:
    JSR(AlternateLengthHandler, 585)
    writeData(Squ1_NoteLenCounter, a);
    y = M(Square1SoundBuffer);
    if (!z)
        goto HandleTriangleMusic;
    a = x;
    a &= BOOST_BINARY(00111110);
    JSR(SetFreq_Squ1, 586)
    if (z)
        goto SkipCtrlL;
    JSR(LoadControlRegs, 587)
SkipCtrlL:
    writeData(Squ1_EnvelopeDataCtrl, a);
    JSR(Dump_Squ1_Regs, 588)
MiscSqu1MusicTasks:
    a = M(Square1SoundBuffer);
    if (!z)
        goto HandleTriangleMusic;
    a = M(EventMusicBuffer);
    a &= BOOST_BINARY(10010001);
    if (!z)
        goto DeathMAltReg;
    y = M(Squ1_EnvelopeDataCtrl);
    if (z)
        goto NoDecEnv2;
    --M(Squ1_EnvelopeDataCtrl);
NoDecEnv2:
    JSR(LoadEnvelopeData, 589)
    writeData(SND_SQUARE1_REG, a);
DeathMAltReg:
    a = M(AltRegContentFlag);
    if (!z)
        goto DoAltLoad;
    a = 0x7f;
DoAltLoad:
    writeData(SND_SQUARE1_REG + 1, a);
HandleTriangleMusic:
    a = M(MusicOffset_Triangle);
    --M(Tri_NoteLenCounter);
    if (!z)
        goto HandleNoiseMusic;
    y = M(MusicOffset_Triangle);
    ++M(MusicOffset_Triangle);
    a = M(W(MusicData) + y);
    if (z)
        goto LoadTriCtrlReg;
    if (!n)
        goto TriNoteHandler;
    JSR(ProcessLengthData, 590)
    writeData(Tri_NoteLenBuffer, a);
    a = 0x1f;
    writeData(SND_TRIANGLE_REG, a);
    y = M(MusicOffset_Triangle);
    ++M(MusicOffset_Triangle);
    a = M(W(MusicData) + y);
    if (z)
        goto LoadTriCtrlReg;
TriNoteHandler:
    JSR(SetFreq_Tri, 591)
    x = M(Tri_NoteLenBuffer);
    writeData(Tri_NoteLenCounter, x);
    a = M(EventMusicBuffer);
    a &= BOOST_BINARY(01101110);
    if (!z)
        goto NotDOrD4;
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(00001010);
    if (z)
        goto HandleNoiseMusic;
NotDOrD4:
    a = x;
    compare(a, 0x12);
    if (c)
        goto LongN;
    a = M(EventMusicBuffer);
    a &= EndOfCastleMusic;
    if (z)
        goto MediN;
    a = 0x0f;
    if (!z)
        goto LoadTriCtrlReg;
MediN:
    a = 0x1f;
    if (!z)
        goto LoadTriCtrlReg;
LongN:
    a = 0xff;
LoadTriCtrlReg:
    writeData(SND_TRIANGLE_REG, a);
HandleNoiseMusic:
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(11110011);
    if (z)
        goto ExitMusicHandler;
    --M(Noise_BeatLenCounter);
    if (!z)
        goto ExitMusicHandler;
FetchNoiseBeatData:
    y = M(MusicOffset_Noise);
    ++M(MusicOffset_Noise);
    a = M(W(MusicData) + y);
    if (!z)
        goto NoiseBeatHandler;
    a = M(NoiseDataLoopbackOfs);
    writeData(MusicOffset_Noise, a);
    if (!z)
        goto FetchNoiseBeatData;
NoiseBeatHandler:
    JSR(AlternateLengthHandler, 592)
    writeData(Noise_BeatLenCounter, a);
    a = x;
    a &= BOOST_BINARY(00111110);
    if (z)
        goto SilentBeat;
    compare(a, 0x30);
    if (z)
        goto LongBeat;
    compare(a, 0x20);
    if (z)
        goto StrongBeat;
    a &= BOOST_BINARY(00010000);
    if (z)
        goto SilentBeat;
    a = 0x1c;
    x = 0x03;
    y = 0x18;
    if (!z)
        goto PlayBeat;
StrongBeat:
    a = 0x1c;
    x = 0x0c;
    y = 0x18;
    if (!z)
        goto PlayBeat;
LongBeat:
    a = 0x1c;
    x = 0x03;
    y = 0x58;
    if (!z)
        goto PlayBeat;
SilentBeat:
    a = 0x10;
PlayBeat:
    writeData(SND_NOISE_REG, a);
    writeData(SND_NOISE_REG + 2, x);
    writeData(SND_NOISE_REG + 3, y);
ExitMusicHandler:
    goto Return;

//---------------------------------------------------------------------

AlternateLengthHandler:
    x = a;
    a.ror();
    a = x;
    a.rol();
    a.rol();
    a.rol();
ProcessLengthData:
    a &= BOOST_BINARY(00000111);
    c = 0;
    a += M(0xf0);
    a += M(NoteLengthTblAdder);
    y = a;
    a = M(MusicLengthLookupTbl + y);
    goto Return;

//---------------------------------------------------------------------

LoadControlRegs:
    a = M(EventMusicBuffer);
    a &= EndOfCastleMusic;
    if (z)
        goto NotECstlM;
    a = 0x04;
    if (!z)
        goto AllMus;
NotECstlM:
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(01111101);
    if (z)
        goto WaterMus;
    a = 0x08;
    if (!z)
        goto AllMus;
WaterMus:
    a = 0x28;
AllMus:
    x = 0x82;
    y = 0x7f;
    goto Return;

//---------------------------------------------------------------------

LoadEnvelopeData:
    a = M(EventMusicBuffer);
    a &= EndOfCastleMusic;
    if (z)
        goto LoadUsualEnvData;
    a = M(EndOfCastleMusicEnvData + y);
    goto Return;

//---------------------------------------------------------------------

LoadUsualEnvData:
    a = M(AreaMusicBuffer);
    a &= BOOST_BINARY(01111101);
    if (z)
        goto LoadWaterEventMusEnvData;
    a = M(AreaMusicEnvData + y);
    goto Return;

//---------------------------------------------------------------------

LoadWaterEventMusEnvData:
    a = M(WaterEventMusEnvData + y);
    goto Return;

//---------------------------------------------------------------------

Return: // Return Handler
    switch(popReturnIndex())
    {
    case 0:
        goto Return_0;
    case 1:
        goto Return_1;
    case 2:
        goto Return_2;
    case 3:
        goto Return_3;
    case 4:
        goto Return_4;
    case 5:
        goto Return_5;
    case 6:
        goto Return_6;
    case 7:
        goto Return_7;
    case 8:
        goto Return_8;
    case 9:
        goto Return_9;
    case 10:
        goto Return_10;
    case 11:
        goto Return_11;
    case 12:
        goto Return_12;
    case 13:
        goto Return_13;
    case 14:
        goto Return_14;
    case 15:
        goto Return_15;
    case 16:
        goto Return_16;
    case 17:
        goto Return_17;
    case 18:
        goto Return_18;
    case 19:
        goto Return_19;
    case 20:
        goto Return_20;
    case 21:
        goto Return_21;
    case 22:
        goto Return_22;
    case 23:
        goto Return_23;
    case 24:
        goto Return_24;
    case 25:
        goto Return_25;
    case 26:
        goto Return_26;
    case 27:
        goto Return_27;
    case 28:
        goto Return_28;
    case 29:
        goto Return_29;
    case 30:
        goto Return_30;
    case 31:
        goto Return_31;
    case 32:
        goto Return_32;
    case 33:
        goto Return_33;
    case 34:
        goto Return_34;
    case 35:
        goto Return_35;
    case 36:
        goto Return_36;
    case 37:
        goto Return_37;
    case 38:
        goto Return_38;
    case 39:
        goto Return_39;
    case 40:
        goto Return_40;
    case 41:
        goto Return_41;
    case 42:
        goto Return_42;
    case 43:
        goto Return_43;
    case 44:
        goto Return_44;
    case 45:
        goto Return_45;
    case 46:
        goto Return_46;
    case 47:
        goto Return_47;
    case 48:
        goto Return_48;
    case 49:
        goto Return_49;
    case 50:
        goto Return_50;
    case 51:
        goto Return_51;
    case 52:
        goto Return_52;
    case 53:
        goto Return_53;
    case 54:
        goto Return_54;
    case 55:
        goto Return_55;
    case 56:
        goto Return_56;
    case 57:
        goto Return_57;
    case 58:
        goto Return_58;
    case 59:
        goto Return_59;
    case 60:
        goto Return_60;
    case 61:
        goto Return_61;
    case 62:
        goto Return_62;
    case 63:
        goto Return_63;
    case 64:
        goto Return_64;
    case 65:
        goto Return_65;
    case 66:
        goto Return_66;
    case 67:
        goto Return_67;
    case 68:
        goto Return_68;
    case 69:
        goto Return_69;
    case 70:
        goto Return_70;
    case 71:
        goto Return_71;
    case 72:
        goto Return_72;
    case 73:
        goto Return_73;
    case 74:
        goto Return_74;
    case 75:
        goto Return_75;
    case 76:
        goto Return_76;
    case 77:
        goto Return_77;
    case 78:
        goto Return_78;
    case 79:
        goto Return_79;
    case 80:
        goto Return_80;
    case 81:
        goto Return_81;
    case 82:
        goto Return_82;
    case 83:
        goto Return_83;
    case 84:
        goto Return_84;
    case 85:
        goto Return_85;
    case 86:
        goto Return_86;
    case 87:
        goto Return_87;
    case 88:
        goto Return_88;
    case 89:
        goto Return_89;
    case 90:
        goto Return_90;
    case 91:
        goto Return_91;
    case 92:
        goto Return_92;
    case 93:
        goto Return_93;
    case 94:
        goto Return_94;
    case 95:
        goto Return_95;
    case 96:
        goto Return_96;
    case 97:
        goto Return_97;
    case 98:
        goto Return_98;
    case 99:
        goto Return_99;
    case 100:
        goto Return_100;
    case 101:
        goto Return_101;
    case 102:
        goto Return_102;
    case 103:
        goto Return_103;
    case 104:
        goto Return_104;
    case 105:
        goto Return_105;
    case 106:
        goto Return_106;
    case 107:
        goto Return_107;
    case 108:
        goto Return_108;
    case 109:
        goto Return_109;
    case 110:
        goto Return_110;
    case 111:
        goto Return_111;
    case 112:
        goto Return_112;
    case 113:
        goto Return_113;
    case 114:
        goto Return_114;
    case 115:
        goto Return_115;
    case 116:
        goto Return_116;
    case 117:
        goto Return_117;
    case 118:
        goto Return_118;
    case 119:
        goto Return_119;
    case 120:
        goto Return_120;
    case 121:
        goto Return_121;
    case 122:
        goto Return_122;
    case 123:
        goto Return_123;
    case 124:
        goto Return_124;
    case 125:
        goto Return_125;
    case 126:
        goto Return_126;
    case 127:
        goto Return_127;
    case 128:
        goto Return_128;
    case 129:
        goto Return_129;
    case 130:
        goto Return_130;
    case 131:
        goto Return_131;
    case 132:
        goto Return_132;
    case 133:
        goto Return_133;
    case 134:
        goto Return_134;
    case 135:
        goto Return_135;
    case 136:
        goto Return_136;
    case 137:
        goto Return_137;
    case 138:
        goto Return_138;
    case 139:
        goto Return_139;
    case 140:
        goto Return_140;
    case 141:
        goto Return_141;
    case 142:
        goto Return_142;
    case 143:
        goto Return_143;
    case 144:
        goto Return_144;
    case 145:
        goto Return_145;
    case 146:
        goto Return_146;
    case 147:
        goto Return_147;
    case 148:
        goto Return_148;
    case 149:
        goto Return_149;
    case 150:
        goto Return_150;
    case 151:
        goto Return_151;
    case 152:
        goto Return_152;
    case 153:
        goto Return_153;
    case 154:
        goto Return_154;
    case 155:
        goto Return_155;
    case 156:
        goto Return_156;
    case 157:
        goto Return_157;
    case 158:
        goto Return_158;
    case 159:
        goto Return_159;
    case 160:
        goto Return_160;
    case 161:
        goto Return_161;
    case 162:
        goto Return_162;
    case 163:
        goto Return_163;
    case 164:
        goto Return_164;
    case 165:
        goto Return_165;
    case 166:
        goto Return_166;
    case 167:
        goto Return_167;
    case 168:
        goto Return_168;
    case 169:
        goto Return_169;
    case 170:
        goto Return_170;
    case 171:
        goto Return_171;
    case 172:
        goto Return_172;
    case 173:
        goto Return_173;
    case 174:
        goto Return_174;
    case 175:
        goto Return_175;
    case 176:
        goto Return_176;
    case 177:
        goto Return_177;
    case 178:
        goto Return_178;
    case 179:
        goto Return_179;
    case 180:
        goto Return_180;
    case 181:
        goto Return_181;
    case 182:
        goto Return_182;
    case 183:
        goto Return_183;
    case 184:
        goto Return_184;
    case 185:
        goto Return_185;
    case 186:
        goto Return_186;
    case 187:
        goto Return_187;
    case 188:
        goto Return_188;
    case 189:
        goto Return_189;
    case 190:
        goto Return_190;
    case 191:
        goto Return_191;
    case 192:
        goto Return_192;
    case 193:
        goto Return_193;
    case 194:
        goto Return_194;
    case 195:
        goto Return_195;
    case 196:
        goto Return_196;
    case 197:
        goto Return_197;
    case 198:
        goto Return_198;
    case 199:
        goto Return_199;
    case 200:
        goto Return_200;
    case 201:
        goto Return_201;
    case 202:
        goto Return_202;
    case 203:
        goto Return_203;
    case 204:
        goto Return_204;
    case 205:
        goto Return_205;
    case 206:
        goto Return_206;
    case 207:
        goto Return_207;
    case 208:
        goto Return_208;
    case 209:
        goto Return_209;
    case 210:
        goto Return_210;
    case 211:
        goto Return_211;
    case 212:
        goto Return_212;
    case 213:
        goto Return_213;
    case 214:
        goto Return_214;
    case 215:
        goto Return_215;
    case 216:
        goto Return_216;
    case 217:
        goto Return_217;
    case 218:
        goto Return_218;
    case 219:
        goto Return_219;
    case 220:
        goto Return_220;
    case 221:
        goto Return_221;
    case 222:
        goto Return_222;
    case 223:
        goto Return_223;
    case 224:
        goto Return_224;
    case 225:
        goto Return_225;
    case 226:
        goto Return_226;
    case 227:
        goto Return_227;
    case 228:
        goto Return_228;
    case 229:
        goto Return_229;
    case 230:
        goto Return_230;
    case 231:
        goto Return_231;
    case 232:
        goto Return_232;
    case 233:
        goto Return_233;
    case 234:
        goto Return_234;
    case 235:
        goto Return_235;
    case 236:
        goto Return_236;
    case 237:
        goto Return_237;
    case 238:
        goto Return_238;
    case 239:
        goto Return_239;
    case 240:
        goto Return_240;
    case 241:
        goto Return_241;
    case 242:
        goto Return_242;
    case 243:
        goto Return_243;
    case 244:
        goto Return_244;
    case 245:
        goto Return_245;
    case 246:
        goto Return_246;
    case 247:
        goto Return_247;
    case 248:
        goto Return_248;
    case 249:
        goto Return_249;
    case 250:
        goto Return_250;
    case 251:
        goto Return_251;
    case 252:
        goto Return_252;
    case 253:
        goto Return_253;
    case 254:
        goto Return_254;
    case 255:
        goto Return_255;
    case 256:
        goto Return_256;
    case 257:
        goto Return_257;
    case 258:
        goto Return_258;
    case 259:
        goto Return_259;
    case 260:
        goto Return_260;
    case 261:
        goto Return_261;
    case 262:
        goto Return_262;
    case 263:
        goto Return_263;
    case 264:
        goto Return_264;
    case 265:
        goto Return_265;
    case 266:
        goto Return_266;
    case 267:
        goto Return_267;
    case 268:
        goto Return_268;
    case 269:
        goto Return_269;
    case 270:
        goto Return_270;
    case 271:
        goto Return_271;
    case 272:
        goto Return_272;
    case 273:
        goto Return_273;
    case 274:
        goto Return_274;
    case 275:
        goto Return_275;
    case 276:
        goto Return_276;
    case 277:
        goto Return_277;
    case 278:
        goto Return_278;
    case 279:
        goto Return_279;
    case 280:
        goto Return_280;
    case 281:
        goto Return_281;
    case 282:
        goto Return_282;
    case 283:
        goto Return_283;
    case 284:
        goto Return_284;
    case 285:
        goto Return_285;
    case 286:
        goto Return_286;
    case 287:
        goto Return_287;
    case 288:
        goto Return_288;
    case 289:
        goto Return_289;
    case 290:
        goto Return_290;
    case 291:
        goto Return_291;
    case 292:
        goto Return_292;
    case 293:
        goto Return_293;
    case 294:
        goto Return_294;
    case 295:
        goto Return_295;
    case 296:
        goto Return_296;
    case 297:
        goto Return_297;
    case 298:
        goto Return_298;
    case 299:
        goto Return_299;
    case 300:
        goto Return_300;
    case 301:
        goto Return_301;
    case 302:
        goto Return_302;
    case 303:
        goto Return_303;
    case 304:
        goto Return_304;
    case 305:
        goto Return_305;
    case 306:
        goto Return_306;
    case 307:
        goto Return_307;
    case 308:
        goto Return_308;
    case 309:
        goto Return_309;
    case 310:
        goto Return_310;
    case 311:
        goto Return_311;
    case 312:
        goto Return_312;
    case 313:
        goto Return_313;
    case 314:
        goto Return_314;
    case 315:
        goto Return_315;
    case 316:
        goto Return_316;
    case 317:
        goto Return_317;
    case 318:
        goto Return_318;
    case 319:
        goto Return_319;
    case 320:
        goto Return_320;
    case 321:
        goto Return_321;
    case 322:
        goto Return_322;
    case 323:
        goto Return_323;
    case 324:
        goto Return_324;
    case 325:
        goto Return_325;
    case 326:
        goto Return_326;
    case 327:
        goto Return_327;
    case 328:
        goto Return_328;
    case 329:
        goto Return_329;
    case 330:
        goto Return_330;
    case 331:
        goto Return_331;
    case 332:
        goto Return_332;
    case 333:
        goto Return_333;
    case 334:
        goto Return_334;
    case 335:
        goto Return_335;
    case 336:
        goto Return_336;
    case 337:
        goto Return_337;
    case 338:
        goto Return_338;
    case 339:
        goto Return_339;
    case 340:
        goto Return_340;
    case 341:
        goto Return_341;
    case 342:
        goto Return_342;
    case 343:
        goto Return_343;
    case 344:
        goto Return_344;
    case 345:
        goto Return_345;
    case 346:
        goto Return_346;
    case 347:
        goto Return_347;
    case 348:
        goto Return_348;
    case 349:
        goto Return_349;
    case 350:
        goto Return_350;
    case 351:
        goto Return_351;
    case 352:
        goto Return_352;
    case 353:
        goto Return_353;
    case 354:
        goto Return_354;
    case 355:
        goto Return_355;
    case 356:
        goto Return_356;
    case 357:
        goto Return_357;
    case 358:
        goto Return_358;
    case 359:
        goto Return_359;
    case 360:
        goto Return_360;
    case 361:
        goto Return_361;
    case 362:
        goto Return_362;
    case 363:
        goto Return_363;
    case 364:
        goto Return_364;
    case 365:
        goto Return_365;
    case 366:
        goto Return_366;
    case 367:
        goto Return_367;
    case 368:
        goto Return_368;
    case 369:
        goto Return_369;
    case 370:
        goto Return_370;
    case 371:
        goto Return_371;
    case 372:
        goto Return_372;
    case 373:
        goto Return_373;
    case 374:
        goto Return_374;
    case 375:
        goto Return_375;
    case 376:
        goto Return_376;
    case 377:
        goto Return_377;
    case 378:
        goto Return_378;
    case 379:
        goto Return_379;
    case 380:
        goto Return_380;
    case 381:
        goto Return_381;
    case 382:
        goto Return_382;
    case 383:
        goto Return_383;
    case 384:
        goto Return_384;
    case 385:
        goto Return_385;
    case 386:
        goto Return_386;
    case 387:
        goto Return_387;
    case 388:
        goto Return_388;
    case 389:
        goto Return_389;
    case 390:
        goto Return_390;
    case 391:
        goto Return_391;
    case 392:
        goto Return_392;
    case 393:
        goto Return_393;
    case 394:
        goto Return_394;
    case 395:
        goto Return_395;
    case 396:
        goto Return_396;
    case 397:
        goto Return_397;
    case 398:
        goto Return_398;
    case 399:
        goto Return_399;
    case 400:
        goto Return_400;
    case 401:
        goto Return_401;
    case 402:
        goto Return_402;
    case 403:
        goto Return_403;
    case 404:
        goto Return_404;
    case 405:
        goto Return_405;
    case 406:
        goto Return_406;
    case 407:
        goto Return_407;
    case 408:
        goto Return_408;
    case 409:
        goto Return_409;
    case 410:
        goto Return_410;
    case 411:
        goto Return_411;
    case 412:
        goto Return_412;
    case 413:
        goto Return_413;
    case 414:
        goto Return_414;
    case 415:
        goto Return_415;
    case 416:
        goto Return_416;
    case 417:
        goto Return_417;
    case 418:
        goto Return_418;
    case 419:
        goto Return_419;
    case 420:
        goto Return_420;
    case 421:
        goto Return_421;
    case 422:
        goto Return_422;
    case 423:
        goto Return_423;
    case 424:
        goto Return_424;
    case 425:
        goto Return_425;
    case 426:
        goto Return_426;
    case 427:
        goto Return_427;
    case 428:
        goto Return_428;
    case 429:
        goto Return_429;
    case 430:
        goto Return_430;
    case 431:
        goto Return_431;
    case 432:
        goto Return_432;
    case 433:
        goto Return_433;
    case 434:
        goto Return_434;
    case 435:
        goto Return_435;
    case 436:
        goto Return_436;
    case 437:
        goto Return_437;
    case 438:
        goto Return_438;
    case 439:
        goto Return_439;
    case 440:
        goto Return_440;
    case 441:
        goto Return_441;
    case 442:
        goto Return_442;
    case 443:
        goto Return_443;
    case 444:
        goto Return_444;
    case 445:
        goto Return_445;
    case 446:
        goto Return_446;
    case 447:
        goto Return_447;
    case 448:
        goto Return_448;
    case 449:
        goto Return_449;
    case 450:
        goto Return_450;
    case 451:
        goto Return_451;
    case 452:
        goto Return_452;
    case 453:
        goto Return_453;
    case 454:
        goto Return_454;
    case 455:
        goto Return_455;
    case 456:
        goto Return_456;
    case 457:
        goto Return_457;
    case 458:
        goto Return_458;
    case 459:
        goto Return_459;
    case 460:
        goto Return_460;
    case 461:
        goto Return_461;
    case 462:
        goto Return_462;
    case 463:
        goto Return_463;
    case 464:
        goto Return_464;
    case 465:
        goto Return_465;
    case 466:
        goto Return_466;
    case 467:
        goto Return_467;
    case 468:
        goto Return_468;
    case 469:
        goto Return_469;
    case 470:
        goto Return_470;
    case 471:
        goto Return_471;
    case 472:
        goto Return_472;
    case 473:
        goto Return_473;
    case 474:
        goto Return_474;
    case 475:
        goto Return_475;
    case 476:
        goto Return_476;
    case 477:
        goto Return_477;
    case 478:
        goto Return_478;
    case 479:
        goto Return_479;
    case 480:
        goto Return_480;
    case 481:
        goto Return_481;
    case 482:
        goto Return_482;
    case 483:
        goto Return_483;
    case 484:
        goto Return_484;
    case 485:
        goto Return_485;
    case 486:
        goto Return_486;
    case 487:
        goto Return_487;
    case 488:
        goto Return_488;
    case 489:
        goto Return_489;
    case 490:
        goto Return_490;
    case 491:
        goto Return_491;
    case 492:
        goto Return_492;
    case 493:
        goto Return_493;
    case 494:
        goto Return_494;
    case 495:
        goto Return_495;
    case 496:
        goto Return_496;
    case 497:
        goto Return_497;
    case 498:
        goto Return_498;
    case 499:
        goto Return_499;
    case 500:
        goto Return_500;
    case 501:
        goto Return_501;
    case 502:
        goto Return_502;
    case 503:
        goto Return_503;
    case 504:
        goto Return_504;
    case 505:
        goto Return_505;
    case 506:
        goto Return_506;
    case 507:
        goto Return_507;
    case 508:
        goto Return_508;
    case 509:
        goto Return_509;
    case 510:
        goto Return_510;
    case 511:
        goto Return_511;
    case 512:
        goto Return_512;
    case 513:
        goto Return_513;
    case 514:
        goto Return_514;
    case 515:
        goto Return_515;
    case 516:
        goto Return_516;
    case 517:
        goto Return_517;
    case 518:
        goto Return_518;
    case 519:
        goto Return_519;
    case 520:
        goto Return_520;
    case 521:
        goto Return_521;
    case 522:
        goto Return_522;
    case 523:
        goto Return_523;
    case 524:
        goto Return_524;
    case 525:
        goto Return_525;
    case 526:
        goto Return_526;
    case 527:
        goto Return_527;
    case 528:
        goto Return_528;
    case 529:
        goto Return_529;
    case 530:
        goto Return_530;
    case 531:
        goto Return_531;
    case 532:
        goto Return_532;
    case 533:
        goto Return_533;
    case 534:
        goto Return_534;
    case 535:
        goto Return_535;
    case 536:
        goto Return_536;
    case 537:
        goto Return_537;
    case 538:
        goto Return_538;
    case 539:
        goto Return_539;
    case 540:
        goto Return_540;
    case 541:
        goto Return_541;
    case 542:
        goto Return_542;
    case 543:
        goto Return_543;
    case 544:
        goto Return_544;
    case 545:
        goto Return_545;
    case 546:
        goto Return_546;
    case 547:
        goto Return_547;
    case 548:
        goto Return_548;
    case 549:
        goto Return_549;
    case 550:
        goto Return_550;
    case 551:
        goto Return_551;
    case 552:
        goto Return_552;
    case 553:
        goto Return_553;
    case 554:
        goto Return_554;
    case 555:
        goto Return_555;
    case 556:
        goto Return_556;
    case 557:
        goto Return_557;
    case 558:
        goto Return_558;
    case 559:
        goto Return_559;
    case 560:
        goto Return_560;
    case 561:
        goto Return_561;
    case 562:
        goto Return_562;
    case 563:
        goto Return_563;
    case 564:
        goto Return_564;
    case 565:
        goto Return_565;
    case 566:
        goto Return_566;
    case 567:
        goto Return_567;
    case 568:
        goto Return_568;
    case 569:
        goto Return_569;
    case 570:
        goto Return_570;
    case 571:
        goto Return_571;
    case 572:
        goto Return_572;
    case 573:
        goto Return_573;
    case 574:
        goto Return_574;
    case 575:
        goto Return_575;
    case 576:
        goto Return_576;
    case 577:
        goto Return_577;
    case 578:
        goto Return_578;
    case 579:
        goto Return_579;
    case 580:
        goto Return_580;
    case 581:
        goto Return_581;
    case 582:
        goto Return_582;
    case 583:
        goto Return_583;
    case 584:
        goto Return_584;
    case 585:
        goto Return_585;
    case 586:
        goto Return_586;
    case 587:
        goto Return_587;
    case 588:
        goto Return_588;
    case 589:
        goto Return_589;
    case 590:
        goto Return_590;
    case 591:
        goto Return_591;
    case 592:
        goto Return_592;
    }
}
