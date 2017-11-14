#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)(実装　HW16A006　池田 仁基)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)(実装:HW16A001 青葉拓希)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)(実装　HW16A006　池田 仁基)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)(実装:HW16A093 島村 幸佑)
// TODO: スコアのサイズを大きくする。(実装:HW16A168 船島 大喜)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(実装:HW16A168 船島 大喜)
// TODO: PlayBGM()関数を使って、BGMを再生する。(実装:HW16A093 島村 幸佑)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H) (実装:HW16A001 青葉拓希)



Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-200, -150);
    targetRect = Rect(200, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_explosion03.mp3");
    }

    // 弾の移動
    if(bulletPos.x>=315){
        bulletPos.x = -999;
    }
    if (bulletPos.x > -999) {
        bulletPos.x += 150 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            PlaySound("se_maoudamashii_explosion06.mp3");
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    if(cloudPos.x <= 350){
        cloudPos.x ++;
    }
    if(cloudPos.x >= 350){
        cloudPos.x = -600;
    }
    
    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    
    if(cannonPos.y <= -70 && Input::GetKeyDown(KeyMask::UpArrow)) {
        cannonPos.y += 10 ;
    }
    if(cannonPos.y >= -140 && Input::GetKeyDown(KeyMask::DownArrow)) {
        cannonPos.y -= 10;
    }
    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 80.0f);
    DrawText(FormatString("%05d", score), Vector2(-309, 169), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-310, 170), Color::white);
}

