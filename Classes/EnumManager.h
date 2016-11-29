#ifndef _ENUM_MANAGER_
#define  _ENUM_MANAGER_

enum class LevelState {
    LevelLoading = 0,
    LevelStart = 1,
    LevelBeginEnd = 2,
    LevelEnd = 3
};

enum class PlayerBulletType{
    Light = 0,
    Rocket = 1,
};

enum class PlayerLightBullet{
    TopLeft = 7,
    Top = 0,
    TopRight = 1,
    Right = 2,
    BotRight = 3,
    Bot = 4,
    BotLeft = 5,
    Left = 6,
    
};

enum class UpgradeItemOrder{
    itemGravity = 8,
    itemRocket = 9,
};

enum class PlayerLightGun{
    TopLeft = 7,
    Top = 0,
    TopRight = 1,
    Right = 2,
    BotRight = 3,
    Bot = 4,
    BotLeft = 5,
    Left = 6,
    
};

enum class Upgrade {
    ChuaCo = 0,
    FirstUpgrade = 1,
    SecondUpgrade = 2,
    FinalUpgrade = 3
};

enum class ShipState {
    NormalState = 0,
    BeginActiveShield = -1,
    ActiveShield = 1,
    BeginInvulnerable = -2,
    Invulnerable = 2,
    BeginDeath = -3,
    Death = 3
};

enum class BarState {
    fadeIn = 0,
    fadeOut = 1
};

enum class ItemState {
    touch = 0,
    untouch = 1
};

enum class TouchState {
    Ngoai = 0,
    TrenItem = 1
};

enum class UnitState {
    Alive = 0,
    Dead = 1
};

enum class BulletType {
    RED_SMALL = 0,
    RED_MEDIUM = 1,
    RED_LARGE = 2,
    RED_EXTRA = 3,
    GREEN_SMALL = 4,
    GREEN_MEDIUM = 5,
    GREEN_LARGE = 6,
    GREEN_EXTRA = 7,
    LAZER_RED = 8,
    LAZER_NONRED = 9,
    LIGHTNING = 10
};

enum class ExplosionType {
    SmallExplosion = 0,
    MediumExplosion = 1,
    LargeExplosion = 2,
    
    SmallExplosionA = 3,
    SmallExplosionB = 4,
    MediumExplosionA = 5,
    MediumExplosionB = 6,
    LargeExplosionA = 7,
    LargeExplosionB = 8,
    
    EnergyExplosion = 9
};

enum class ShipHpLevel {
    BeginHP = 50,
    FirstHP = 70,
    SecondHP = 110,
    FinalHP = 170
};

enum class ShipSpeedLevel {
    BeginShipSpeed = 2,
    FirstShipSpeed = 3,
    SecondShipSpeed = 4,
    FinalShipSpeed = 5
};

enum class TypeCoin {
    typeSilverCoin = 0,
    typeGoldCoin = 1,
    typeGoldBar = 2,
    typeDiamond = 3,
    typeShield = 4,
    typeMedic = 5,
    typeLife = 6,
    typeTreasure = TypeCoin::typeDiamond | TypeCoin::typeGoldBar | TypeCoin::typeGoldCoin | TypeCoin::typeSilverCoin | TypeCoin::typeShield | TypeCoin::typeMedic | TypeCoin::typeLife,
};

enum class TypeMedal {
    typeSilverMedal = 0,
    typeGoldMedal = 1,
    typeDiamondMedal = 2
};

enum class TypeOtherItem {
    typeMultiplier = 0,
    typeShield = 1,
    typeLife = 2
};

enum class BossState {
    stateNull = -1,
    stateBeginStart = 0,
    stateStart = 1,
    stateBeginActive = 2,
    stateActive = 3,
    stateBeginDead = 4,
    stateDead = 5
};

enum class typeLazer {
    typeRedLazer = 0,
    typeNonRedLazer = 1
};

enum class RocketState {
    stateTarget = 0,
    stateNonTarget = 1
};

enum class MissionState {
    stateLock = 0,
    stateUnlock = 1
};

enum class ComboType {
    ComboStart = 0,
    Combo20 = 1,
    Combo40 = 2,
    Combo80 = 3,
    Combo120 = 4,
    Combo160 = 5,
    Combo200 = 6,
    Combo240 = 7,
    Combo280 = 8,
    Combo300 = 9,
    ComboImmortal = 10,
    ComboBreak = 11
};

enum class PhysicCategory{
    None = 0,
    Enemy = (1 << 0),
    Bullet = (1 << 1),
    BackGround = (1 << 2),
    Item = (1 << 3),
    PlayerShip = (1 << 4),
    Bar = (1 << 5),
    EnemyBullet = (1 << 6),
    Boss = (1 << 7),
    Lightning = (1 << 8),
    combo1 = PhysicCategory::Bar | PhysicCategory::Item | PhysicCategory::EnemyBullet | PhysicCategory:: Boss | PhysicCategory::Enemy | PhysicCategory::Lightning,
    combo2 = PhysicCategory::Bullet | PhysicCategory::PlayerShip | PhysicCategory::Lightning,
    combo3 = PhysicCategory::Enemy | PhysicCategory::Boss ,
    
};

enum class PhysicsGroup{
    GROUP_0 = 1, //Include bar and ship only
};

enum class TagObject{
    Bar = 1,
    Ship = 2
};

#endif
