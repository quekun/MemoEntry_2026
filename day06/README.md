1）学习了手动编写AiControlle子类逻辑以及ai行为树的知识，实际运用是以ai行为树为主



2）创建了一个服务和三个任务实现ai行为树，

BTService\_PlayerLocationIfSeen，不断更新两个key

BTTask\_ClearBlackboardValue，清空LastKnownPlayerLocation

BTTask\_FindRandomRoamPoint巡逻

BTTaskNode\_Fire开火



分为三个状态

随机巡逻：基于NavMesh计算随机可达点实现全图游走，并接入DetourCrowdAIController人群避让系统，有效避免多AI寻路时发生拥堵扎堆



动态感知：开发专属感知Service，利用双黑板键独立管理并实时更新玩家的当前坐标PlayerLocation与最后已知位置LastKnownPlayerLocation



战术决策：AI锁定目标即触发追击与开火；若目标脱离视野，行为树会切入调查状态，驱动AI前往最后已知位置侦察。驻留确认无果后，自动清空数据并恢复巡逻

