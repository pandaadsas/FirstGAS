# FirstGAS

基于 **Unreal Engine 5.7** 的 Gameplay Ability System（GAS）学习项目。在官方第三人称模板的基础上，从零手写了一套基于 GAS 的角色属性框架：网络复制的属性集、AbilitySystemComponent 扩展、用 GameplayEffect 初始化属性、重叠体积类效果道具，以及服务端 / 客户端双路径的 AbilityActorInfo 初始化流程。

## 功能特性

- **属性集 `MyAttributeSet`**
  - Health / MaxHealth、Mana / MaxMana、Stamina / MaxStamina、MoveSpeed、Damage
  - 全部基于 `FGameplayAttributeData`，通过 `DOREPLIFETIME_CONDITION_NOTIFY` + `OnRep` 回调做网络复制
  - 在 `PostGameplayEffectExecute` 中对数值做 Clamp，防止越界
- **ASC 扩展 `MyAbilitySystemComponent`**
  - `AddCharacterAbilities` / `AddCharacterPassiveAbilities`：批量授予主动与被动技能
  - `InitializeDefaultAttributes`：应用默认属性 GameplayEffect
- **ASC 挂载在 PlayerState（`MyPlayerState`）**
  - 多人模式下的推荐做法，角色重生后属性不丢失
  - 实现 `IAbilitySystemInterface`，暴露蓝图纯函数 `GetMyAbilitySystemComponent` / `GetMyAttributeSet`
- **角色初始化 `FirstGASCharacter`**
  - `PossessedBy`（服务端）/ `OnRep_PlayerState`（客户端）双路径调用 `InitAbilityActorInfo`
  - 监听 ASC 的属性变化 Delegate，广播 `OnHealthChanged` / `OnManaChanged` 给 UMG 做 HUD
  - 通过 `CharacterTag`（GameplayTag）区分角色类型
- **职业配置资产 `CharacterClassInfo`**
  - DataAsset，`TMap<FGameplayTag, FCharacterClassDefaultInfo>`
  - 一个 GameplayTag 映射到「默认属性 GE + 起始技能 + 起始被动」，换职业只改配置
- **效果道具 `EffectActor`**
  - Box 重叠检测，对进入的角色应用对应的 GameplayEffect（回血 / 扣血 / 加速等）
- **背包组件 `InventoryComponent`**
  - 基于 GameplayTag 的物品容器 `TMap<FGameplayTag, int32>`
  - `AddItem` 通过 Server RPC（`ServerAddItem`）在服务端记账
- **蓝图工具库 `MyBlueprintLibrary`**
  - 继承自 `UAbilitySystemBlueprintLibrary`，提供 `GetCharacterClassDefaultInfo` 等便捷接口

## 项目结构

```text
Source/FirstGAS/
├── FirstGASGameMode / FirstGASPlayerController    # 模板根目录的基础框架
├── MyGAS/                                         # 自己实现的 GAS 模块
│   ├── Character/FirstGASCharacter                # 第三人称角色 + IAbilitySystemInterface
│   ├── Data/CharacterClassInfo                    # 职业默认配置 DataAsset
│   ├── MyAbilitySystemComponent                   # ASC 扩展：授技 / 初始化属性
│   ├── MyAttributeSet                             # 属性集：血 / 蓝 / 体力 / 移速
│   ├── MyPlayerState                              # ASC 与 AttributeSet 的持有者
│   ├── MyGameMode                                 # 提供职业配置访问
│   ├── Inventory/InventoryComponent               # GameplayTag 背包组件（Server RPC）
│   ├── PlayerController/MyPlayerController        # PlayerController 扩展
│   ├── EffectActor                                # 重叠应用 GameplayEffect 的道具
│   └── MyBlueprintLibrary                         # 蓝图工具函数
└── Variant_Combat / Variant_Platforming / Variant_SideScrolling
    （Epic 官方第三人称模板自带的示例变体，仅作参考保留）
```

```text
Content/_MyGAS/
├── Map/M_Startup                  # 测试用主地图
└── Blueprint/
    ├── AbilitySyaytem/Attribute   # GE_DefaultAttribute：默认属性 GameplayEffect
    ├── Data/GA_ClassInfo          # CharacterClassInfo 配置资产
    ├── GameMode/BP_MyGameMode
    ├── Player/                    # BP_ThirdPersonCharacter、BP_MyPlayerState 等
    │   └── PickupEffects/         # BP_HealthUp / BP_HealthDown 及对应 GameplayEffect
    └── UI/Overlay/W_Overlay       # 属性 HUD 覆层
```

## 环境要求

| 依赖 | 版本 |
| --- | --- |
| Unreal Engine | 5.7 |
| Visual Studio | 2022（含「使用 C++ 的游戏开发」工作负载） |
| 插件 | GameplayAbilities（GAS）、StateTree、GameplayStateTree |

## 运行方式

1. 双击 `FirstGAS.uproject` 打开工程（首次打开会触发编译）；
2. 或右键 `.uproject` → *Generate Visual Studio project files*，生成解决方案后编译 `Development Editor` 再打开；
3. 进入 `Content/_MyGAS/Map/M_Startup` 地图，走到效果道具（EffectActor）附近即可看到属性变化与 UI 更新。

## 学习路线（本项目的实现顺序）

1. `PlayerState` 上创建 `AbilitySystemComponent` 与 `AttributeSet`
2. 写 `MyAttributeSet`，补齐复制与 Clamp 逻辑
3. 用 `CharacterClassInfo` + GameplayEffect 初始化默认属性
4. 在 Character 中做服务端 / 客户端双路径的 `InitAbilityActorInfo`
5. 监听属性变化 Delegate，把数值广播给 UMG
6. 实现 `EffectActor` 做 GameplayEffect 的实际消耗 / 回复
7. 实现 `InventoryComponent`：Server RPC + GameplayTag 背包

## 致谢

- [Epic Games 官方第三人称模板](https://www.unrealengine.com/) 与 Variant 示例（Variant_Combat / Variant_Platforming / Variant_SideScrolling）
- [GASDocumentation](https://github.com/tranek/GASDocumentation) —— 社区最全面的 GAS 中文/英文学习资料

---

仅供学习交流使用。
