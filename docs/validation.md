# Runtime Validation

The lab was validated with Unreal Engine 5.8 in development mode on 2026-10-13.

## Build

Both targets completed successfully with Unreal Build Tool:

- `ReplicationLab Win64 Development`
- `ReplicationLabEditor Win64 Development`

The build was limited to one parallel action to fit the available memory on the development machine.

## Two-process replication test

1. Started the project in game mode as a listen server on `/Engine/Maps/Entry?listen`, with `-ReplicationLabSelfTest` enabled.
2. The authority log confirmed the `ReplicationLabGameMode`, an open port `7777`, the generated arena and Energy Node, then a server-side state change to `Charge=100` and `Activations=1`.
3. Started a separate game-mode client connected to `127.0.0.1:7777`.
4. The client log confirmed the server welcome and `OnRep_ChargeState` receiving `Charge=100` and `Activations=1`.

This verifies the intended authority boundary and replication path. It does not replace manual PIE interaction testing with two windows; follow the README steps when changing input, collision, camera, or presentation.
