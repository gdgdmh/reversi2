#include "Move.h"

#include "../../util/Assert.h"
#include "Board.h"

/**
 * コンストラクタ
 */
reversi::Move::Move() {}

/**
 * デストラクタ
 */
reversi::Move::~Move() {}

/**
 * 石の置かれていない場所を探す
 * @param board          盤データ
 * @param emptyPositions 結果をいれるための参照渡しオブジェクト
 */
void reversi::Move::FindEmptyPosition(
    const reversi::Board& board,
    reversi::ReversiConstant::EMPTY_POSITION& emptyPosition) {
  // データをクリアしておく
  emptyPosition.position.clear();

  int size = reversi::ReversiConstant::POSITION_SIZE;
  const reversi::Board::BOARD boardData = board.GetRawData();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(
        i, size, "Move::FindEmptyPosition() position index over");
    // 位置を取得
    reversi::ReversiConstant::POSITION position =
        (reversi::ReversiConstant::POSITION)
            reversi::ReversiConstant::POSITIONS[i];

    reversi::Assert::AssertArrayRange(
        (int)position, reversi::ReversiConstant::BOARD_SIZE,
        "Move::FindEmptyPosition() board index over");

    reversi::ReversiConstant::BOARD_INFO info =
        (reversi::ReversiConstant::BOARD_INFO)
            boardData.boardData[(int)position];
    if (info == reversi::ReversiConstant::BOARD_INFO::NONE) {
      // 石が置かれていない場所を保持する
      emptyPosition.position.push_back(position);
    }
  }
}

/**
 * 打てる場所を探す
 * このデータはキャッシュされる
 * @param board          盤データ
 * @param emptyPositions 石の置かれてない場所が入ったデータ
 * @param turn           手番(黒,白)
 */
void reversi::Move::FindPutEnablePosition(
    const reversi::Board& board,
    const reversi::ReversiConstant::EMPTY_POSITION& emptyPosition,
    reversi::ReversiConstant::TURN turn) {
  // キャッシュをクリアする
  moveCacheEnableMove.reverseInfo.clear();

  // 空いている場所からその場所に打てるかチェック
  size_t size = emptyPosition.position.size();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(i, (int)size,
                                      "Move::FindPutEnablePosition index over");
    reversi::ReversiConstant::POSITION position = emptyPosition.position[i];
    // その場所に打てるかチェック
    reversi::ReverseInfo reverseInfo =
        GetEnableMoveInfo(board, (int)position, turn);
    if (reverseInfo.IsEnableMove()) {
      // キャッシュする
      moveCacheEnableMove.reverseInfo.push_back(reverseInfo);
    }
  }
}

/**
 * 打つことができるか
 * 予めキャッシュを作成しておくこと
 * @param  position チェックする位置
 * @return          trueならその位置に打つことができる
 */
bool reversi::Move::CheckEnableMoveByCache(
    reversi::ReversiConstant::POSITION position) const {
  size_t size = moveCacheEnableMove.reverseInfo.size();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(
        i, (int)size, "Move::CheckEnableMoveByCache index over");
    if (position == moveCacheEnableMove.reverseInfo[i].GetPosition()) {
      return true;
    }
  }
  // 空いてない位置などを指定した
  return false;
}

/**
 * どこかに打てるか
 * 予めキャッシュを作成しておくこと
 * @return trueならどこかに打てる
 */
bool reversi::Move::CheckSomewherePutEnableByCache() {
  size_t size = moveCacheEnableMove.reverseInfo.size();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(
        i, (int)size, "Move::CheckEnableMoveByCache index over");
    if (moveCacheEnableMove.reverseInfo[i].IsEnableMove()) {
      // どこかには打てる
      return true;
    }
  }
  // どこにも打てない
  return false;
}

/**
 * 裏返し情報の取得
 * 予めキャッシュを作成しておくこと
 * @param  position 位置
 * @return          裏返し情報
 */
const reversi::ReverseInfo reversi::Move::GetReverseInfo(
    reversi::ReversiConstant::POSITION position) const {
  size_t size = moveCacheEnableMove.reverseInfo.size();
  for (int i = 0; i < size; ++i) {
    reversi::Assert::AssertArrayRange(i, (int)size,
                                      "Move::GetReverseInfo index over");
    if (position == moveCacheEnableMove.reverseInfo[i].GetPosition()) {
      // 位置が一致した裏返し情報を返す
      return moveCacheEnableMove.reverseInfo[i];
    }
  }
  // 見つからなかった(CheckEnableMoveByCacheでチェックしておけば起こらないはず)
  reversi::Assert::AssertEqual(0, "Move::GetReverseInfo not found");
  reversi::ReverseInfo info(reversi::ReversiConstant::POSITION::A1,
                            reversi::ReversiConstant::TURN::TURN_BLACK);
  return info;
}

/**
 * 裏返し情報の取得(index)
 * 予めキャッシュを作成しておくこと
 * @param  index 裏返し情報のindex
 * @return       [description]
 */
const reversi::ReverseInfo& reversi::Move::GetReverseInfoByIndex(
    int index) const {
  reversi::Assert::AssertArrayRange(index,
                                    (int)moveCacheEnableMove.reverseInfo.size(),
                                    "Move::GetReverseInfoByIndex index over");
  return moveCacheEnableMove.reverseInfo[index];
}

/**
 * 裏返し情報のデータ数取得
 * @return 裏返し情報データ数
 */
int reversi::Move::GetReverseInfoSize() const {
  return (int)moveCacheEnableMove.reverseInfo.size();
}

/**
 * その場所に打つことができるか情報を取得する
 * @param  board    盤データ
 * @param  position 打とうとする盤の位置
 * @param  turn     手番(黒,白)
 * @return          trueならその位置に打つことができる
 */
reversi::ReverseInfo reversi::Move::GetEnableMoveInfo(
    const reversi::Board& board, int position,
    reversi::ReversiConstant::TURN turn) {
  reversi::ReverseInfo info((reversi::ReversiConstant::POSITION)position, turn);
  bool isEnable = false;

  const int MAX_DIRECTION = 8;
  reversi::Move::DIRECTION directions[MAX_DIRECTION] = {
      reversi::Move::DIRECTION::UP,        reversi::Move::DIRECTION::DOWN,
      reversi::Move::DIRECTION::LEFT,      reversi::Move::DIRECTION::RIGHT,
      reversi::Move::DIRECTION::UP_LEFT,   reversi::Move::DIRECTION::UP_RIGHT,
      reversi::Move::DIRECTION::DOWN_LEFT, reversi::Move::DIRECTION::DOWN_RIGHT,
  };
  // それぞれの方向に対して打てるかチェック
  // 将来的にはpositionの位置に対してチェックする方向を減らすなど(一番左のマスは左側に対するチェックをしないなど)
  // 負荷軽減案はあるがいったん確実性を取る
  for (int i = 0; i < MAX_DIRECTION; ++i) {
    reversi::Assert::AssertArrayRange(i, MAX_DIRECTION,
                                      "Move::GetEnableMoveInfo index over");
    if (CheckMoveInfoDirection(board, info, position, directions[i], turn)) {
      isEnable = true;
    }
  }
  return info;
}

/**
 * その位置の指定方向に打つことができるか、情報を取得する
 * @param  board       盤データ
 * @param  reverseInfo 裏返し情報
 * @param  position    打とうとする盤の位置
 * @param  direction   チェックする方向
 * @param  turn        手番(黒,白)
 * @return             trueならその方向に打つことができる
 */
bool reversi::Move::CheckMoveInfoDirection(
    const reversi::Board& board, reversi::ReverseInfo& reverseInfo,
    int position, reversi::Move::DIRECTION direction,
    reversi::ReversiConstant::TURN turn) {
  const reversi::Board::BOARD boardData = board.GetRawData();

  // 盤のオフセットを取得
  int offset = ToDirectionOffset(direction);

  int currentPosition = position;
  reversi::Assert::AssertArrayRange(
      currentPosition, reversi::ReversiConstant::BOARD_SIZE,
      "Move::CheckEnableMoveDirection() board index over");
  reversi::ReversiConstant::BOARD_INFO info =
      (reversi::ReversiConstant::BOARD_INFO)
          boardData.boardData[currentPosition];
  if (info != reversi::ReversiConstant::BOARD_INFO::NONE) {
    // 指定位置は空でなければそもそも打てない
    return false;
  }
  // 次の方向の位置
  currentPosition += offset;

  bool loop = true;
  bool isSandwichStarted = false;  // 挟まれているか
  int sandwichCount = 0;           // 挟まれている数
  reversi::ReverseInfo::DIRECTION reverseInfoDirection =
      ToReverseInfoDirection(direction);
  while (loop) {
    // 盤情報取得
    reversi::Assert::AssertArrayRange(
        currentPosition, reversi::ReversiConstant::BOARD_SIZE,
        "Move::CheckEnableMoveDirection() board index over(loop)");
    reversi::ReversiConstant::BOARD_INFO info =
        (reversi::ReversiConstant::BOARD_INFO)
            boardData.boardData[currentPosition];
    // 挟まれている状態の取得
    reversi::Move::SANDWICH_STATUS status =
        GetSandwichInfo(isSandwichStarted, sandwichCount, turn, info);
    switch (status) {
      case SANDWICH_STATUS::SANDWICH_OK:
        return true;
      case SANDWICH_STATUS::SANDWICH_CONTINUE:
        // 取得できる石の位置を記憶
        reverseInfo.AddReversePosition(
            reverseInfoDirection,
            (reversi::ReversiConstant::POSITION)currentPosition);
        break;
      case SANDWICH_STATUS::SANDWICH_NG_INVALID:
      case SANDWICH_STATUS::SANDWICH_NG_EMPTY:
      case SANDWICH_STATUS::SANDWICH_NG_SELF:
        // 結果として取れないと判断されたため、裏返した情報はクリアしておく
        reverseInfo.ClearReversePosition(reverseInfoDirection);
        return false;
      default:
        reverseInfo.ClearReversePosition(reverseInfoDirection);
        return false;
    }
    // 次の方向の位置
    currentPosition += offset;
  }
  return false;
}

/**
 * 位置から盤のオフセットを取得する
 * @param  direction 方向
 * @return           盤のオフセット
 */
int reversi::Move::ToDirectionOffset(reversi::Move::DIRECTION direction) {
  int position = 0;  // オフセットだけ欲しいので0とする
  switch (direction) {
    case DIRECTION::UP:
      return reversi::ReversiConstant::GetPositionUp(position);
    case DIRECTION::DOWN:
      return reversi::ReversiConstant::GetPositionDown(position);
    case DIRECTION::LEFT:
      return reversi::ReversiConstant::GetPositionLeft(position);
    case DIRECTION::RIGHT:
      return reversi::ReversiConstant::GetPositionRight(position);
    case DIRECTION::UP_LEFT:
      return reversi::ReversiConstant::GetPositionUpLeft(position);
    case DIRECTION::UP_RIGHT:
      return reversi::ReversiConstant::GetPositionUpRight(position);
    case DIRECTION::DOWN_LEFT:
      return reversi::ReversiConstant::GetPositionDownLeft(position);
    case DIRECTION::DOWN_RIGHT:
      return reversi::ReversiConstant::GetPositionDownRight(position);
    default:
      reversi::Assert::AssertEqual(
          0, "Move::ToDirectionOffset() invalid direction");
      return 0;
  }
}

/**
 * 挟まれている情報の取得
 * @param  isSandwichStarted 挟まれているか
 * @param  sandwichCount     いくつ挟まれているか
 * @param  turn              手番(黒,白)
 * @param  info              盤の情報
 * @return                   状態
 */
reversi::Move::SANDWICH_STATUS reversi::Move::GetSandwichInfo(
    bool& isSandwichStarted, int& sandwichCount,
    reversi::ReversiConstant::TURN turn,
    reversi::ReversiConstant::BOARD_INFO info) {
  if (info == reversi::ReversiConstant::BOARD_INFO::INVALID) {
    // 無効マスがあったので挟まれていない
    return reversi::Move::SANDWICH_STATUS::SANDWICH_NG_INVALID;
  }
  if (info == reversi::ReversiConstant::BOARD_INFO::NONE) {
    // 空マスがあったので挟まれていない
    return reversi::Move::SANDWICH_STATUS::SANDWICH_NG_EMPTY;
  }

  if (info == reversi::ReversiConstant::BOARD_INFO::BLACK) {
    if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
      if (isSandwichStarted) {
        // 挟んでいる状態で自分の石があったので挟んでいる
        return reversi::Move::SANDWICH_STATUS::SANDWICH_OK;
      } else {
        // 挟んでいない状態で自分の石があったら挟まれてない
        return reversi::Move::SANDWICH_STATUS::SANDWICH_NG_SELF;
      }
    } else if (turn == reversi::ReversiConstant::TURN::TURN_WHITE) {
      // 相手の石なので挟まれている + 石をカウント
      isSandwichStarted = true;
      ++sandwichCount;
      return reversi::Move::SANDWICH_STATUS::SANDWICH_CONTINUE;
    }
  }
  if (info == reversi::ReversiConstant::BOARD_INFO::WHITE) {
    if (turn == reversi::ReversiConstant::TURN::TURN_BLACK) {
      // 相手の石なので挟まれている + 石をカウント
      isSandwichStarted = true;
      ++sandwichCount;
      return reversi::Move::SANDWICH_STATUS::SANDWICH_CONTINUE;
    } else if (turn == reversi::ReversiConstant::TURN::TURN_WHITE) {
      if (isSandwichStarted) {
        // 挟んでいる状態で自分の石があったので挟んでいる
        return reversi::Move::SANDWICH_STATUS::SANDWICH_OK;
      } else {
        // 挟んでいない状態で自分の石があったら挟まれてない
        return reversi::Move::SANDWICH_STATUS::SANDWICH_NG_SELF;
      }
    }
  }
  // ここには来ないはず
  reversi::Assert::AssertEqual(0, "Move::GetSandwichInfo() invalid status");
  return reversi::Move::SANDWICH_STATUS::SANDWICH_NG_UNKNOWN;
}

/**
 * DIRECTON型をReverseInfoのDIRECTION型に変換する
 * @param  direction 方向
 * @return           ReverseInfoのDIRECTION
 */
reversi::ReverseInfo::DIRECTION reversi::Move::ToReverseInfoDirection(
    reversi::Move::DIRECTION direction) {
  switch (direction) {
    case DIRECTION::UP:
      return reversi::ReverseInfo::DIRECTION::UP;
    case DIRECTION::DOWN:
      return reversi::ReverseInfo::DIRECTION::DOWN;
    case DIRECTION::LEFT:
      return reversi::ReverseInfo::DIRECTION::LEFT;
    case DIRECTION::RIGHT:
      return reversi::ReverseInfo::DIRECTION::RIGHT;
    case DIRECTION::UP_LEFT:
      return reversi::ReverseInfo::DIRECTION::UP_LEFT;
    case DIRECTION::UP_RIGHT:
      return reversi::ReverseInfo::DIRECTION::UP_RIGHT;
    case DIRECTION::DOWN_LEFT:
      return reversi::ReverseInfo::DIRECTION::DOWN_LEFT;
    case DIRECTION::DOWN_RIGHT:
      return reversi::ReverseInfo::DIRECTION::DOWN_RIGHT;
    default:
      return reversi::ReverseInfo::DIRECTION::UP;
  }
}
