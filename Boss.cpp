#include <Novice.h>
#include <math.h>
#include "Boss.h"

// コンストラクタ
Boss::Boss()
{
	Initialize();
}

// デストラクタ
Boss::~Boss()
{}

// ボスの初期化処理
void Boss::Initialize()
{
	// ボス本体の位置を設定
	x = 640;
	/*y = 360;*/

	// 眼球の初期位置をボスの中心に設定
	eyeX = 640.0f;
	eyeY = 360.0f;

	// 眼球の追尾速度を設定
	eyeSpeed = 0.5f;

	// ボスの最大HP
	maxHp = 500;
	// 現在のHPと同期
	hp = maxHp;

	// -------------------------
	// ダメージの初期化
	// -------------------------

	damageTimer = 0;
	damageDuration = 20;
	amplitude = 15;

	// シェイク
	shakeX = 0.0f;
	shakeY = 0.0f;

	// 点滅
	isBlink = false;

	// -------------------------
	// 攻撃の初期化
	// -------------------------

	attackType = ATTACK_NONE;
	attackTimer = 0;
	isAttacking = false;

	// -------------------------
	// 行動管理の初期化
	// -------------------------

	//// 最初は画面内で待機
	//state = IDLE;

	//// ボス本体のY座標
	//bossY = 360.0f;

	//デバック用(あとで消す)
	// まだ行動を開始していない
	isStarted = false;

	// 最初は画面外で待機
	state = WAIT;

	// ボス本体のY座標
	bossY = -250.0f;

	// 眼球も画面外に配置
	eyeX = (float)x;
	eyeY = bossY;

	// 行動時間
	stateTimer = 0;

	// 画面内にいる時間（60FPSで15秒）
	idleDuration = 60 * 15;

	// イージング用
	easingTimer = 0.0f;
	startY = 0.0f;
	endY = 0.0f;

	// 画面内移動用
	moveTime = 0.0f;
	moveSpeed = 1.0f;
	moveRange = 100.0f;

	// キー入力の初期化(デバック用)
	preLKey = 0;

}

// ボスの更新処理
void Boss::Update(float playerX, float playerY)
{
	//// ボスの行動状態を更新
	//UpdateState(playerX, playerY);

	//デバック用(あとで消す)
	// Lキーの入力状態を取得
	int currentLKey = Novice::CheckHitKey(DIK_L);

	// Lキーを押した瞬間
	if (currentLKey && !preLKey && !isStarted)
	{

		// 行動開始
		isStarted = true;

		// 待機状態からスタート
		state = WAIT;
		stateTimer = 0;

		// ボスを画面外に配置
		x = 640.0f;
		bossY = -250.0f;

		// 眼球もボスの中心に配置
		eyeX = (float)x;
		eyeY = bossY;
	}

	// キーの状態を保存
	preLKey = currentLKey;

	// 行動開始後だけ状態を更新
	if (isStarted)
	{
		UpdateState();
	}

	// IDLE中だけプレイヤーを追いかける
	if (state == IDLE)
	{
		eyeX += (playerX - eyeX) * eyeSpeed;
		eyeY += (playerY - eyeY) * eyeSpeed;
	}

	// ボスの中心から眼球までの距離を計算
	float dx = eyeX - x;
	float dy = eyeY - bossY;

	// 2点間の距離を計算
	float distance = sqrtf(dx * dx + dy * dy);

	// 眼球が移動できる最大距離
	float maxDistance = 190.0f - 78.0f;

	// 移動できる範囲を超えた場合
	if (distance > maxDistance)
	{
		float rate = maxDistance / distance;

		eyeX = x + dx * rate;
		eyeY = bossY + dy * rate;
	}

	// ダメージ演出
	if (damageTimer > 0 && damageDuration > 0)
	{
		float currentTime = (float)damageTimer / damageDuration;

		shakeX = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;
		shakeY = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;

		isBlink = (damageTimer / 3) % 2 == 0;

		damageTimer--;
	}
	else
	{
		shakeX = 0.0f;
		shakeY = 0.0f;
		isBlink = false;
	}

	// 攻撃処理
	UpdateAttack();
}

//// ボスの眼球移動
//void Boss::Update(float playerX, float playerY)
//{
//	// プレイヤーの方向に眼球を移動させる
//	eyeX += (playerX - eyeX) * eyeSpeed;
//	eyeY += (playerY - eyeY) * eyeSpeed;
//
//	// ボスの中心から眼球までの距離を計算
//	float dx = eyeX - x;
//	float dy = eyeY - y;
//
//	// 2点間の距離を計算
//	float distance = sqrtf(dx * dx + dy * dy);
//
//	// 眼球が移動できる最大距離
//	// 外側の円の半径190 - 眼球の半径78
//	float maxDistance = 190.0f - 78.0f;
//
//	// 眼球が移動できる範囲を超えた場合
//	if (distance > maxDistance)
//	{
//		// 距離の比率を計算
//		float rate = maxDistance / distance;
//
//		// 眼球を移動できる範囲の端に戻す
//		eyeX = x + dx * rate;
//		eyeY = y + dy * rate;
//
//	}
//
//	// ダメージ演出
//	if (damageTimer > 0 && damageDuration > 0)
//	{
//		// 今の時間 / 最大時間 = 割合
//		float currentTime = (float)damageTimer / damageDuration;
//
//		// 割合 × 揺れ幅
//		shakeX = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;
//		shakeY = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;
//
//		// 3フレームごとに点滅
//		isBlink = (damageTimer / 3) % 2 == 0;
//
//		damageTimer--;
//	} 
//	else
//	{
//		// 揺れと点滅をリセット
//		shakeX = 0.0f;
//		shakeY = 0.0f;
//		isBlink = false;
//	}
//
//	UpdateAttack();
//
//}

// ボスの行動状態を更新
void Boss::UpdateState()
{
	switch (state)
	{
	case WAIT:
		// 待機時間を計測
		stateTimer++;

		// しばらく待ったら攻撃開始
		if (stateTimer >= 60 * 2)
		{
			stateTimer = 0;
			state = ATTACK;
		}
		break;

	case ATTACK:
		// 攻撃が終了したら登場
		if (!isAttacking)
		{
			stateTimer = 0;
			easingTimer = 0.0f;

			startY = -250.0f;
			endY = 360.0f;

			bossY = startY;

			state = ENTER;
		}
		break;

	case ENTER:
		// 画面内に登場
		easingTimer += 0.02f;

		if (easingTimer >= 1.0f)
		{
			easingTimer = 1.0f;
			bossY = endY;
			stateTimer = 0;
			moveTime = 0.0f;

			state = IDLE;
		} 
		else
		{
			// EaseOutCubic
			float t = 1.0f - powf(1.0f - easingTimer, 3.0f);
			bossY = startY + (endY - startY) * t;
		}
		break;

	case IDLE:

		// 画面内をゆっくり漂う
		stateTimer++;
		moveTime += 0.01f;

		// 左右の移動
		x = 640.0f + sinf(moveTime * 0.7f) * 250.0f;

		// 上下の移動
		bossY = 360.0f + cosf(moveTime) * 120.0f;

		// 一定時間経過したら眼球を中央に戻す
		if (stateTimer >= idleDuration)
		{
			stateTimer = 0;
			state = RETURN_EYE;
		}
		break;

	case RETURN_EYE:
		// 眼球をボスの中心に戻す
		eyeX += (x - eyeX) * 0.08f;
		eyeY += (bossY - eyeY) * 0.08f;

		// 十分中央に近づいたら退場準備
		if (fabsf(eyeX - x) < 1.0f &&
			fabsf(eyeY - bossY) < 1.0f)
		{
			eyeX = (float)x;
			eyeY = bossY;

			stateTimer = 0;
			easingTimer = 0.0f;
			startY = bossY;
			endY = bossY + 50.0f;

			state = EXIT_PREPARE;
		}
		break;

	case EXIT_PREPARE:
		// 少し下に下がる
		easingTimer += 0.05f;

		if (easingTimer >= 1.0f)
		{
			easingTimer = 1.0f;
			bossY = endY;

			easingTimer = 0.0f;
			startY = bossY;
			endY = -300.0f;

			state = EXIT;
		} 
		else
		{
			float t = easingTimer * easingTimer;
			bossY = startY + (endY - startY) * t;
		}
		break;

	case EXIT:
		// 上方向へ加速しながら退場
		easingTimer += 0.025f;

		if (easingTimer >= 1.0f)
		{
			bossY = endY;
			stateTimer = 0;
			state = WAIT;

			// 行動終了
			isStarted = false;
		}
		else
		{
			float t = easingTimer * easingTimer * easingTimer;
			bossY = startY + (endY - startY) * t;
		}
		break;
	}
}

// ボスにダメージを与える
void Boss::TakeDamage(int damage)
{
	// HPを減らす
	hp -= damage;

	// HPが0より小さくならないようにする
	if (hp < 0)
	{
		hp = 0;
	}

	// ダメージ演出を開始
	damageTimer = damageDuration;
}

// ボスの描画
void Boss::Draw()
{
	if (!isStarted)
	{
		return;
	}

	// シェイクを加算したボスの座標
	int bossDrawX = (int)x + (int)shakeX;
	int bossDrawY = (int)bossY + (int)shakeY;

	if (!isBlink)
	{
		// 外側の円
		Novice::DrawEllipse
		(
			bossDrawX,
			bossDrawY,
			190,
			190,
			0.0f,
			0xFF2040FF,
			kFillModeWireFrame
		);

		// 白い眼球
		Novice::DrawEllipse
		(
			static_cast<int>(eyeX + shakeX),
			static_cast<int>(eyeY + shakeY),
			78,
			78,
			0.0f,
			WHITE,
			kFillModeSolid
		);

		// 赤い瞳
		Novice::DrawEllipse
		(
			static_cast<int>(eyeX + shakeX),
			static_cast<int>(eyeY + shakeY),
			50,
			50,
			0.0f,
			0xFF2040FF,
			kFillModeSolid
		);

		for (int i = -180; i < 180; i++)
		{
			// 線の始点と終点のX座標
			float x1 = static_cast<float>(i);
			float x2 = static_cast<float>(i + 1);

			// 上下の曲線のY座標を計算
			float y1 = 90.0f * (1.0f - (x1 * x1) / (180.0f * 180.0f));
			float y2 = 90.0f * (1.0f - (x2 * x2) / (180.0f * 180.0f));

			// 目の上下の輪郭
			// 上側の曲線
			Novice::DrawLine
			(
				static_cast<int>(bossDrawX + x1),
				static_cast<int>(bossDrawY - y1),
				static_cast<int>(bossDrawX + x2),
				static_cast<int>(bossDrawY - y2),
				0xFF2040FF
			);

			// 下側の曲線
			Novice::DrawLine
			(
				static_cast<int>(bossDrawX + x1),
				static_cast<int>(bossDrawY + y1),
				static_cast<int>(bossDrawX + x2),
				static_cast<int>(bossDrawY + y2),
				0xFF2040FF
			);
		}

		DrawAttack();
	}

	/* // ボスの外側の円
	Novice::DrawEllipse
	(
		640,
		360,
		190,
		190,
		0.0f,
		0xFF2040FF,
		kFillModeWireFrame
	);

	// 白い眼球
	Novice::DrawEllipse
	(
		static_cast<int>(eyeX),
		static_cast<int>(eyeY),
		78,
		78,
		0.0f,
		WHITE,
		kFillModeSolid
	);

	 // 赤い瞳
	Novice::DrawEllipse
	(
		static_cast<int>(eyeX),
		static_cast<int>(eyeY),
		50,
		50,
		0.0f,
		0xFF2040FF,
		kFillModeSolid
	);

	 // 目の上下の輪郭を描画
	for (int i = -180; i < 180; i++)
	{
		 // 線の始点と終点のX座標
		float x1 = static_cast<float>(i);
		float x2 = static_cast<float>(i + 1);

		 // 上下の曲線のY座標を計算
		float y1 = 90.0f * (1.0f - (x1 * x1) / (180.0f * 180.0f));
		float y2 = 90.0f * (1.0f - (x2 * x2) / (180.0f * 180.0f));

		 // 上側の曲線
		Novice::DrawLine
		(
			static_cast<int>(640 + x1),
			static_cast<int>(360 - y1),
			static_cast<int>(640 + x2),
			static_cast<int>(360 - y2),
			0xFF2040FF
		);

		 // 下側の曲線
		Novice::DrawLine
		(
			static_cast<int>(640 + x1),
			static_cast<int>(360 + y1),
			static_cast<int>(640 + x2),
			static_cast<int>(360 + y2),
			0xFF2040FF
		);
	}*/

	// ------------------------------
	// ボスのHPバー
	// ------------------------------

	// HPバーの位置
	int hpBarX = 120;
	int hpBarY = 40;

	// HPバーの大きさ
	int hpBarWidth = 1200;
	int hpBarHeight = 30;

	// 現在のHPの割合を計算
	float hpRate = static_cast<float>(hp) / maxHp;
	// 現在のHPに合わせてバーの幅を計算
	int currentHpWidth = static_cast<int>(hpBarWidth * hpRate);

	// HPバーの背景（黒）
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		hpBarWidth,
		hpBarHeight,
		0.0f,
		BLACK,
		kFillModeSolid
	);

	// HPの残量（赤）
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		currentHpWidth,
		hpBarHeight,
		0.0f,
		0xFF2040FF,
		kFillModeSolid
	);

	// HPバーの白い枠線
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		hpBarWidth,
		hpBarHeight,
		0.0f,
		WHITE,
		kFillModeWireFrame
	);

}