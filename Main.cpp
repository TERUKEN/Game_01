#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Common.h"
#include "Game.h"
#include "Player.h"
#include "Graph.h"


/***********************************************
* 変数の宣言
***********************************************/
int OldKey;		// 前回の入力キー
int NowKey;		// 今回の入力キー
int KeyFlg;		// 入力キー情報
int GameMode = 0; // ゲームモード

/***********************************************
*　構造体の宣言
***********************************************/




/***********************************************
* プログラムの開始
***********************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	SetMainWindowText( "!!!" );		// タイトルを設定

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	SetGraphMode(800,600,16);		// 画面大きさ(横・縦・色域)

	if ( DxLib_Init() == -1 ) return -1;	// DX ライブラリの初期化処理

	SetDrawScreen( DX_SCREEN_BACK );		// 描画先画面を裏にする

	if ( LoadImages() == -1 ) return -1;	// 画像読込み関数を呼び出し

	// ゲームループ
	while ( ProcessMessage() == 0 && GameMode != 99 && !(KeyFlg & PAD_INPUT_START)){
		
		// 入力キー取得
		OldKey = NowKey;
		NowKey = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
		KeyFlg = NowKey & ~OldKey;

		ClearDrawScreen(); // 画面の初期化

		switch (GameMode){
			case 0:
			GameInit();		//ゲーム初期処理
			break;
			
			case 1:
			GameMain();		//ゲームメイン処理
			break;
		}

		ScreenFlip(); // 裏画面の内容を表画面に反映
	}
	
	DxLib_End();	// DX ライブラリ使用の終了処理
	return 0;	// ソフトの終了
}

