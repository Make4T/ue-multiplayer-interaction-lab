# UE Multiplayer Interaction Lab

A compact Unreal Engine 5.8 C++ project that demonstrates a server-authoritative interaction flow and replicated gameplay state.

## Demonstrated systems

- Listen-server multiplayer test flow.
- Client input sent through a server RPC.
- Server-side range validation.
- Replicated charge state with `OnRep` visual updates.
- Replicated activation counter.
- Runtime HUD showing net mode, local role and shared state.
- Self-contained runtime lighting for consistent visibility on the engine Entry map.

## Interaction flow

```text
Client presses E
  -> local line trace finds Energy Node
  -> ServerInteract RPC
  -> server validates actor and range
  -> server toggles ChargePercent and ActivationCount
  -> replicated properties reach all clients
  -> OnRep updates light, scale, label and HUD
```

## Run locally

1. Open `ReplicationLab.uproject` with Unreal Engine 5.8.
2. Set Play mode to **Listen Server** and **Number of Players = 2**.
3. Start PIE, walk to the Energy Node, aim at it and press `E`.
4. Verify that both windows show the same charge state and activation count.

The project generates its small arena and Energy Node at runtime, so it has no dependency on external art assets or on the Thalassofobia project.

## Automated runtime verification

The repository includes an opt-in `-ReplicationLabSelfTest` launch flag for development verification. On the authority, it creates the demo world and toggles the Energy Node once. A client joining the listen server receives the replicated state through `OnRep_ChargeState`.

Validated on Unreal Engine 5.8:

- Game and editor targets compile successfully.
- A listen server started on port `7777` with `-ReplicationLabSelfTest` creates the arena and toggles the node to `Charge=100`, `Activations=1`.
- A separate client joins `127.0.0.1:7777` and logs the replicated node state through `OnRep_ChargeState`.

See [docs/validation.md](docs/validation.md) for the exact evidence and scope.

# ue-multiplayer-interaction-lab
