# Architecture

`AReplicationLabCharacter` owns local input and only requests interaction. It never changes the shared Energy Node state directly.

`AReplicationLabEnergyNode` is replicated and always relevant. Its charge and activation count are replicated properties. The server alone changes them after distance validation; every peer applies presentation changes through `OnRep_ChargeState`.

`AReplicationLabHUD` reads the local network role and replicated node state to make the test observable in both PIE windows.

The arena, node and player pawns are spawned by `AReplicationLabGameMode`, making the demo self-contained and safe to run on the engine Entry map.

