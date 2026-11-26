#include <Novice.h>
#include "BossAttack.h"

// 攻撃処理
void BossAttack::Update()
{
	if (!isAttacking)
	{
		return;
	}

	attackTimer++;

	switch (attackType)
	{
	case ATTACK_RUSH:
		//突進

		break;

	case ATTACK_BEAM:
		// ビームの処理

		break;

	case ATTACK_BALL:
		// 球の処理
		break;

	case ATTACK_WAVE:
		// 衝撃波の処理
		break;

	default:
		break;
	}
}

// 攻撃描画
void BossAttack::DrawAttack()
{
	switch (attackType)
	{
	case ATTACK_BEAM:
		// ビームの描画
		break;

	case ATTACK_BALL:
		// 球の描画
		break;

	case ATTACK_WAVE:
		// 衝撃波の描画
		break;

	default:
		break;
	}
}
