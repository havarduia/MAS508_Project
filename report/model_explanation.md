# How to write Section 2: Mathematical Model

Notes for writing Section 2 of the report, matched to our layout:

| Report section | Holds | Does NOT hold |
|---|---|---|
| 1 Introduction | task, specs table, **BOM table** (`tab:bom`) | equations |
| **2 Mathematical Model** | rig description, assumptions, equations, state space, all with **symbols** | any measurement or experiment |
| 3 System Identification | every measurement: `k_s`, `b_s`, input gain, `τ_m`, validation, what the model misses | derivations |

Rule of thumb: if a sentence says "we measured" or contains a measured number (`k_s = 131.7`, `b_s = 0.0048`,
`τ_m = 18 ms`), it goes in Section 3. Section 2 refers forward with "identified in Section~\ref{sec:ident}".
Datasheet values from Table 1 (`R`, `L`, `k_i`, `J_m`, lead) are fine in Section 2, because they are not measured.

The model is `src/model/plant_model.m`. Lecture references: L2a/L2b (DC motor, state space), L2b/L2c
(equilibrium point), L3b/L3c (controllability/observability).

---

## Proposed subsections of Section 2

1. System Description and Assumptions
2. Motor and Ball Screw
3. Equations of Motion
4. Equilibrium Point
5. State-Space Model (including the sensor state)

Below is what to write in each one: the content, the equations, and the one-line "why".

---

## 2.1 System Description and Assumptions

**Say:** the chain of parts, which signal is the input, which is measured, which is not.

```
voltage v -> BLDC motor -> ball screw -> actuator (nut + carriage) -> spring/damper -> payload
                           rotation ->     position y (not measured)   k_s, b_s        position x (measured)
                           translation
```

- Input: motor voltage `v` (limited to ±5 V).
- Output: payload position `x` from the inductive sensor at the bottom. The **only** measured signal.
- Actuator position `y`: not measured, stroke 0–25 mm. Refer to Table~\ref{tab:bom} for the hardware.

**Why a linear state-space model:** LQR, the Kalman filter and the controllability/observability tests all
need the form `ẋ = Ax + Bu`, `output = Cx`. The stroke is small, so a linear model is reasonable.

**Assumptions (list them explicitly):**
1. Only the axial (vertical) motion is modelled (project description 3.1). Sideways swing and twisting are ignored.
   - Do **not** call it "single degree of freedom". The model has two masses moving independently (`y` and `x`),
     so it is two mechanical DOFs. Write "only vertical motion" instead.
2. The ball screw is rigid with no backlash: `y = θ/N`.
3. Ball-screw efficiency `η = 1` (prescribed). The real value is below 1 and unknown; it is kept as a symbol in
   the equations and treated as uncertainty (robustness checks, Section 4).
4. Linear spring `k_s` and linear viscous damper `b_s`. Both unknown, identified in Section 3.
5. No friction in the screw or the motor driver. (Section 3 shows it exists; integral control handles it.)
6. The BLDC motor with its driver is modelled as a DC motor: KVL plus a torque constant.

**Notation warning:** the lectures write the output as `y = Cx`, but here `y` is the *unmeasured* actuator. Write
the output as `x` (later `x_s`) so `y` always means the actuator.

**Do not put here:** the free-decay idea for `b_s`, the "pulse not step" remark, the ruler test. All Section 3.

---

## 2.2 Motor and Ball Screw

**Motor (KVL + torque, L2a/L2b):**

$$ L\frac{di}{dt} = v - R\,i - k_b\,\omega_m, \qquad T_m = k_i\, i $$

- `R = 0.55 Ω`, `L = 0.8 mH`, `k_i = k_b = 0.036` (Table 1).
- Electrical time constant `L/R = 1.45 ms`, much faster than the rest of the system.

**Ball screw (Appendix K):** the lead `l = 10 mm` gives the screw ratio

$$ N = \frac{2\pi}{l} = 628.3\ \text{rad/m}, \qquad \omega_m = N\dot y, \qquad F = \eta N T . $$

- `F = ηNT` is Appendix K's `T = F l/(2πη)` turned around.
- One sentence of intuition: the screw is a gearbox with ratio `N`. It multiplies torque into force by `ηN` and
  divides speed by `N`.

---

## 2.3 Equations of Motion

**Actuator with the motor inertia.** Newton for the rotor (`J_m ω̇_m = k_i i − T_L`) and for the carriage
(`m_a ÿ = ηN T_L − F_spring`). Eliminate the load torque `T_L` and use `ω_m = Nẏ`:

$$ M_e\,\ddot y = K_f\, i - k_s (y-x) - b_s(\dot y-\dot x) $$

**Payload (Newton):**

$$ m_l\,\ddot x = k_s (y-x) + b_s(\dot y-\dot x) $$

**Voltage equation** with the back emf written in actuator speed:

$$ L\frac{di}{dt} = v - R\,i - K_b\,\dot y $$

**Lumped constants (put in a small table):**

| Constant | Formula | Value (Table 1, η = 1) | Meaning |
|---|---|---|---|
| `K_f` | `η k_i N` | 22.6 N/A | actuator force per ampere |
| `K_b` | `k_b N` | 22.6 V/(m/s) | back emf per actuator speed |
| `M_e` | `m_a + η J_m N²` | 28.7 kg | effective moving mass |
| `τ_m` | `M_e R/(K_f K_b)` | 30.9 ms | actuator (mechanical) time constant |

**Worth one paragraph:** the reflected motor inertia `η J_m N² = 28.4 kg` is about 100× the carriage mass
`m_a = 0.3 kg`. Because of the fine lead, the actuator behaves like a 29 kg mass. That makes it slow compared with
the 0.51 kg payload, and the payload barely disturbs the actuator.

**Forward reference:** `τ_m` is the one Table 1-derived value that Section 3 changes (to 18 ms from the frequency
response). Just say "`τ_m` is checked against rig data in Section~\ref{sec:gain}". No 18 ms here.

---

## 2.4 Equilibrium Point (gravity drops out, L2b/L2c)

**Say:** with absolute positions, gravity appears in both Newton equations (`−m_l g`, `−m_a g`) and needs a constant
holding current. Measuring every state from the static equilibrium (operating) point removes these constant terms.

- At equilibrium the spring is stretched by `Δ₀ = m_l g / k_s` (symbolic here; the number is in Section 3, where
  38 mm matches the ruler test).
- The motor carries a constant holding current `(m_a + m_l) g / K_f ≈ 0.35 A` (datasheet values only, so fine here).
- Since the model is already linear, this is the L2c linearisation about the operating point, with no approximation.
- One sentence: on the rig the holding voltage is the bias `v_bias = 0.6 V` (more than `R·0.35 A = 0.19 V` because of
  friction). The controller adds `v_bias`; the model works in deviations from it.

All positions in 2.3 are deviations from this point. Say that once, right after the equations.

---

## 2.5 State-Space Model

**State choice:** one state per energy store: inductor current, and position + velocity of each mass.

$$ \mathbf{x} = [\,i\;\; y\;\; \dot y\;\; x\;\; \dot x\,]^T, \qquad u = v, \qquad \text{output} = x $$

A, B, C as already in `doc.tex`. Explain the rows in one sentence each:
- row 1: KVL solved for `di/dt`;
- rows 2 and 4: velocity is the derivative of position;
- row 3: actuator Newton divided by `M_e`;
- row 5: payload Newton divided by `m_l`.

**Sensor state:** the Balluff sensor has a lag (datasheet: −3 dB at 15 Hz). Model it as a first-order lag:

$$ \dot x_s = \frac{x - x_s}{\tau_s}, \qquad \tau_s = 10.6\ \text{ms}, \qquad \text{output} = x_s $$

- Six states. `C` picks `x_s`.
- Why it matters: the lag costs phase near 6 Hz, where the first controller was close to instability.
- `τ_s` comes from the datasheet, so it can stay in Section 2.

**Also mention in a sentence:** in the code the input gain enters as `B = k_v/L`. `k_v = 1` is pure Table 1;
Section 3 finds `k_v = 0.99`.

---

## Model checks: poles, controllability, observability

These need the identified `k_s`, `b_s` and `τ_m`, so place them at the **end of Section 3** (an "Identified model"
paragraph before Model Validation) or at the start of Section 4. If you prefer to keep them as the last paragraph of
Section 2, add "with the parameters identified in Section 3".

**Open-loop poles** (`plant_model` with no outputs prints them):

| Pole | Table 1 model | Final model (τm 18 ms, with sensor) | Meaning |
|---|---|---|---|
| electrical | −653 | −627 | ≈ R/L, very fast |
| mechanical | −34 | −61 | ≈ 1/τ_m |
| sensor | – | −94 | 1/τ_s |
| **0** | 0 | 0 | integrator: constant voltage gives constant actuator *speed* |
| payload mode | −0.06 ± 16.09j | −0.07 ± 16.08j | 2.56 Hz, ζ ≈ 0.004, nearly undamped |

Comment on two of them:
1. **The pole at 0.** The actuator integrates voltage into position, so in open loop it drifts to the end stop.
   This is why the identification uses short pulses or closed-loop tests (Section 3 intro).
2. **The payload mode** sits almost on the imaginary axis. This is the oscillation the controller must remove.
   Its small damping comes mostly from the back emf (the payload drags the actuator, which induces current),
   not from `b_s` alone (which would give ζ = 0.0003).

**Observability (L3c):** `rank(obsv(A, C)) = 6`. All states can be estimated from `x_s` alone, so an observer is possible.

**Controllability (L3b, Lab 6):** `rank(ctrb(A, B))` returns too low a rank numerically, because the entries span
many orders of magnitude. The Hautus test in `ctrb_calc.m`, `rank([λI − A, B]) = n` for every eigenvalue,
gives full rank, so the system is controllable. One sentence on this shows why the course gives the Hautus test.

---

## Things that belong in Section 3, not here

| Topic | Section 3 subsection |
|---|---|
| ruler test, `k_s = m_l g/Δx = 131.7 N/m` | Spring Coefficient |
| free decay, log decrement, `b_s = 0.0048 Ns/m`, `k_s` cross-check 127.5 N/m | Damping Coefficient |
| "open-loop tests must be short pulses" | Section 3 intro |
| input gain 0.66 (open-loop pulse, `validate_step.m`) → 0.99 (closed-loop FRF), `τ_m` 18 ms | Input Gain and Actuator Time Constant |
| pulse response rig vs model | Model Validation |
| friction, driver dead band, uncertainty table | What the Model Does Not Capture |

---

## Code pointers

- `src/model/plant_model.m`: builds A, B, C as above. Arguments: `η`, `k_v`, `τ_m`, `τ_s`, `m_l`. Final model:
  `plant_model(1, 0.99, 0.018, 0.0106)`. No outputs → prints `M_e`, `K_f`, holding current, static stretch, poles.
- `src/model/ctrb_calc.m`: Hautus test (course file).
- `src/model/build_plant_blockdiagram.m` → `figures/plant_blockdiagram.png`: the same equations as a Simulink block
  diagram, if you want a figure in 2.3. Each integrator output is one state.
