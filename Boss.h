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

// ボス待機状態
enum BossState
{
	WAIT,           // 画面外で待機
	ATTACK,         // 攻撃中
	ENTER,          // 画面内に登場
	IDLE,           // 画面内を移動
	RETURN_EYE,     // 眼球が中央に戻る
	EXIT_PREPARE,   // 少し下に下がる
	EXIT            // 上方向に退場
};

class Boss
{
public:

	Boss();
	~Boss();
	// ボスの初期化
	void Initialize();
	// ボスの攻撃受けた時(演出)
	void BossDamage();
	// プレイヤーの座標を受け取ってボスを更新する
	void Update(float playerX, float playerY);
	// ボスを描画する
	void Draw();

	// テストプレイ用の関数ですあとで消すよ
	void TakeDamage(int damage);

private:

	// ボス本体の中心座標
	float x;
	/*int y;*/

	// 眼球の座標
	float eyeX;
	float eyeY;
	// 眼球がプレイヤーを追いかける速度
	float eyeSpeed;

	// ボスの体力
	int hp;
	// ボスの最大HP
	int maxHp;

	// -------------------------
	// ダメージ関連
	// -------------------------
	int damageTimer;
	int damageDuration;
	int amplitude;

	// シェイク
	float shakeX;
	float shakeY;

	// 点滅
	bool isBlink;

	// -------------------------
	// 攻撃関連
	// -------------------------

	// 現在の攻撃種類
	AttackType attackType;

	// 攻撃経過時間
	int attackTimer;

	// 攻撃中かどうか
	bool isAttacking;

	// 攻撃処理
	void UpdateAttack();

	// 攻撃描画
	void DrawAttack();

	// -------------------------
	// ボスの行動管理
	// -------------------------

	// 現在の行動状態
	BossState state;

	// ボス本体のY座標
	float bossY;

	// 行動時間管理
	int stateTimer;

	// 画面内にいる時間
	int idleDuration;

	// イージング用
	float easingTimer;
	float startY;
	float endY;

	// 画面内移動用
	float moveTime;
	float moveSpeed;
	float moveRange;

	//デバック用あとで消す
	// ボスの行動を開始したか
	bool isStarted;
	// Lキーの前フレームの状態
	int preLKey;

	//// ボスの状態更新
	//void UpdateState(float playerX, float playerY);

	//// ボスの状態更新
	void UpdateState();

	// イージング関数
	float EaseInBack(float t);

};