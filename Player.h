#pragma once
#include "Vector2.h"

class Player
{
public:
	Player();
	void Update(const char keys[256], const char preKeys[256]);
	void Draw();
	// プレイヤーのX座標を取得
	float GetX() const;
	float GetY() const;

private:
	Vector2 position_;
	Vector2 dashDirection_;	 // ダッシュ方向
	Vector2 gaugePosition_;  // ゲージの位置
	Vector2 gaugeSize_;      // ゲージのサイズ

	float size_;			 // プレイヤーのサイズ
	float speed_;			 // プレイヤーの移動速度
	int dashFrame_;          // ダッシュの残り時間
	float dashSpeed_;        // ダッシュ速度
	int dashCooldown_;       // ダッシュのクールタイム
	int kDashCooldownMax_;   // ダッシュのクールタイムの最大値
	float dashCooldownRate_; // クールタイムの回復割合
};