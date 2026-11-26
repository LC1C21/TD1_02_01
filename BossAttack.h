#pragma once

// ボスの攻撃種類
enum AttackType
{
	ATTACK_RUSH,
	ATTACK_NONE,
	ATTACK_BEAM,
	ATTACK_BALL,
	ATTACK_WAVE
};

// 突撃の種類
enum RushState
{
	RUSH_WAIT,
	RUSH_WARNING,
	RUSH_DASH,
	RUSH_INTERVAL,
	RUSH_FINISH
};

class BossAttack
{
public:

	BossAttack();
	~BossAttack();

	// ボスの初期化
	void Initialize();
	// 攻撃状態の更新
	void Update();
	// 攻撃の描画
	void Draw();

private:
	// 現在の攻撃種類
	AttackType attackType;

	// 攻撃経過時間
	int attackTimer;

	// 攻撃中かどうか
	bool isAttacking;

	////攻撃処理
	//void BossAttack();

	//攻撃描画
	void DrawAttack();

};
