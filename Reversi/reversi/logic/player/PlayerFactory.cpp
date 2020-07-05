#include "PlayerFactory.h"
#include "../../util/Assert.h"
#include "../../util/OutputConsole.h"
#include "PlayerMan.h"
#include "PlayerCpu.h"

/**
 * コンストラクタ
 */
reversi::PlayerFactory::PlayerFactory() {
}

/**
 * デストラクタ
 */
reversi::PlayerFactory::~PlayerFactory() {
}

/**
 * プレイヤーの生成
 * @param  type プレイヤーのタイプ
 * @return      生成されたプレイヤー
 */
reversi::IPlayer* reversi::PlayerFactory::Create(reversi::PlayerFactory::TYPE type) {
	switch (type) {
	case reversi::PlayerFactory::TYPE::PLAYER_MAN:
		return new PlayerMan();
	case reversi::PlayerFactory::TYPE::PLAYER_CPU1:
		return new PlayerCpu(reversi::PlayerCpu::LEVEL::LEVEL1);
	case reversi::PlayerFactory::TYPE::PLAYER_CPU2:
		return new PlayerCpu(reversi::PlayerCpu::LEVEL::LEVEL2);
	case reversi::PlayerFactory::TYPE::PLAYER_CPU3:
		return new PlayerCpu(reversi::PlayerCpu::LEVEL::LEVEL3);
	case reversi::PlayerFactory::TYPE::PLAYER_CPU4:
		return new PlayerCpu(reversi::PlayerCpu::LEVEL::LEVEL4);
	default:
		return NULL;
	}
}
