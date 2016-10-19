#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Common.h"
#include "Game.h"
#include "Player.h"
#include "Graph.h"


/***********************************************
* �ϐ��̐錾
***********************************************/
int OldKey;		// �O��̓��̓L�[
int NowKey;		// ����̓��̓L�[
int KeyFlg;		// ���̓L�[���
int GameMode = 0; // �Q�[�����[�h

/***********************************************
*�@�\���̂̐錾
***********************************************/




/***********************************************
* �v���O�����̊J�n
***********************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	SetMainWindowText( "!!!" );		// �^�C�g����ݒ�

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(800,600,16);		// ��ʑ傫��(���E�c�E�F��)

	if ( DxLib_Init() == -1 ) return -1;	// DX ���C�u�����̏���������

	SetDrawScreen( DX_SCREEN_BACK );		// �`����ʂ𗠂ɂ���

	if ( LoadImages() == -1 ) return -1;	// �摜�Ǎ��݊֐����Ăяo��

	// �Q�[�����[�v
	while ( ProcessMessage() == 0 && GameMode != 99 && !(KeyFlg & PAD_INPUT_START)){
		
		// ���̓L�[�擾
		OldKey = NowKey;
		NowKey = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
		KeyFlg = NowKey & ~OldKey;

		ClearDrawScreen(); // ��ʂ̏�����

		switch (GameMode){
			case 0:
			GameInit();		//�Q�[����������
			break;
			
			case 1:
			GameMain();		//�Q�[�����C������
			break;
		}

		ScreenFlip(); // ����ʂ̓��e��\��ʂɔ��f
	}
	
	DxLib_End();	// DX ���C�u�����g�p�̏I������
	return 0;	// �\�t�g�̏I��
}

