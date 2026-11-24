#include <Novice.h>
#include <math.h>
#include <cmath>
#include "Player.h"

Player::Player()
{
	position_.x = 0.0f;
	position_.y = 0.0f;
	dashDirection_.x = 0.0f;
	dashDirection_.y = 0.0f;
	gaugePosition_.x = 0.0f;
	gaugePosition_.y = 0.0f;
	gaugeSize_.x = 60.0f;
	gaugeSize_.y = 8.0f;
	size_ = 32.0f;
	speed_ = 6.0f;
	dashFrame_ = 0;
	dashSpeed_ = 15.0f;
	dashCooldown_ = 0;
	kDashCooldownMax_ = 120;
	dashCooldownRate_ = 1.0f;
}

void Player::Update(const char keys[256], const char preKeys[256])
{
	// ダッシュのクールタイムを減らす
	if (dashCooldown_ > 0)
	{
		dashCooldown_--;
	}

	// 移動方向
	Vector2 move = { 0.0f, 0.0f };

	// プレイヤーの移動処理
	// 上に移動
	if (keys[DIK_W])
	{
		move.y -= 1.0f;
	}

	// 下に移動
	if (keys[DIK_S])
	{
		move.y += 1.0f;
	}

	// 左に移動
	if (keys[DIK_A])
	{
		move.x -= 1.0f;
	}

	// 右に移動
	if (keys[DIK_D])
	{
		move.x += 1.0f;
	}

	// 斜め移動の速度を統一
	float length = sqrtf(move.x * move.x + move.y * move.y);

	// 移動ベクトルを正規化
	if (length > 0.0f)
	{
		move.x /= length;
		move.y /= length;
	}

	// SPACEを押した瞬間にダッシュ開始
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && dashFrame_ == 0 && length > 0.0f && dashCooldown_ == 0)
	{
		dashFrame_ = 10;
		dashDirection_ = move;
		dashCooldown_ = kDashCooldownMax_;
	}

	// ダッシュ中
	if (dashFrame_ > 0)
	{
		position_.x += dashDirection_.x * dashSpeed_;
		position_.y += dashDirection_.y * dashSpeed_;

		dashFrame_--;
	} else
	{
		// 通常移動
		position_.x += move.x * speed_;
		position_.y += move.y * speed_;
	}

	// ゲージの位置をプレイヤーの位置に合わせる
	gaugePosition_.x = position_.x - gaugeSize_.x / 4.3f;
	gaugePosition_.y = position_.y - gaugeSize_.y;

	// クールタイムの回復割合を計算
	dashCooldownRate_ = 1.0f - static_cast<float>(dashCooldown_) / kDashCooldownMax_;
}

void Player::Draw()
{
	// プレイヤーの描画処理
	Novice::DrawBox
	(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(size_),
		static_cast<int>(size_),
		0.0f,
		0x00FFFFFF,
		kFillModeSolid
	);

	// ダッシュのクールタイムがある場合、ゲージを描画
	if (dashCooldown_ > 0)
	{
		// 
		Novice::DrawBox
		(
			static_cast<int>(gaugePosition_.x),
			static_cast<int>(gaugePosition_.y + 50.0f),
			static_cast<int>(gaugeSize_.x),
			static_cast<int>(gaugeSize_.y),
			0.0f,
			0x404040FF,
			kFillModeSolid
		);

		// ゲージの残り時間を描画
		Novice::DrawBox
		(
			static_cast<int>(gaugePosition_.x),
			static_cast<int>(gaugePosition_.y + 50.0f),
			static_cast<int>(gaugeSize_.x * dashCooldownRate_),
			static_cast<int>(gaugeSize_.y),
			0.0f,
			0x00FFFFFF,
			kFillModeSolid
		);
	}
}

// プレイヤーのX座標を返す
float Player::GetX() const
{
	return position_.x + size_ / 2.0f;
}

// プレイヤーのY座標を返す
float Player::GetY() const
{
	return position_.y + size_ / 2.0f;
}