1）创建了HealthComponet与OnHit函数，当子弹击中Enemy时，使用ApllyDamage函数触发OnComponentHit事件，并把该事件绑定到OnHit函数中，执行减少生命值，生命值为空时，调用Destroy()销毁敌人actor

2）在TankHeroGameMode中添加了游戏相关规则，创建TArray<AActor*> Enemies指针数组，通过UGameplayStatics::GetAllActorsOfClass函数，得到敌人数量，当敌人数量清零或者tank生命值归零时，在日志输出对应文本，并且设定了计时器，游戏开始前会打印倒计时。

3）在tank类里面添加了开火冷却计数器，避免按下一次发射多发子弹的问题，通过SetPlayerEnabled(bool Enabled)函数，在游戏开始前拒绝输入



