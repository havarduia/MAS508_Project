# MAS508 Project Report: Outline

Title: State observer and feedback control of a spring-suspended payload
Group members (names on the front page, required).
Target: about 15 pages plus appendix. Each section answers "what did we do, and why".
Course references are given as L2a, L3d, and so on.

---

## 1. Introduction (½ page)
- The task in one paragraph: lift the payload to x0 + 15 mm and lower it to x0 + 5 mm, with only the payload position x measured.
- Specs from the project description, section 3.3: fast settling, little oscillation, zero steady-state error, the same controller for 15→5 and 20→5 mm, robust to a push and to the real ball-screw efficiency (η < 1, not known exactly), |v| ≤ 5 V, stroke 0–25 mm.
- Report structure in two sentences.

## 2. System and model (2–3 pages)
- Figure: the rig with the quantities y, x and x0 marked (as Fig. 3 of the project description).
- Equations (L2a/L2b):
  - Motor: KVL for the current, torque = ki·i.
  - Ball screw: force from torque, using the lead l and the efficiency η. The model uses η = 1 as the project description prescribes; the real η < 1 is treated as uncertainty.
  - Actuator mass: Newton's law with the spring and damper force.
  - Payload: Newton's law.
- States are deviations from the static equilibrium, so gravity drops out (L2b/L2c).
  The holding voltage (0.6 V, measured) is the equilibrium input.
- State-space model with states [i, y, ẏ, x, ẋ]. Input v, output x.
- Sensor lag added as a sixth state x_s (the Balluff updates about every 14 ms, ≈ 10.6 ms effective lag).
- Controllability and observability: rank of ctrb/obsv, checked with the Hautus test (ctrb_calc.m, Lab 6).
- Why a linear model: LQR and Kalman need one, and the stroke is small (≤ 25 mm).

## 3. Identification and validation (3 pages)
The project description asks for evaluation "in the frequency domain, time domain, or a combination of both". We use both: time domain as the main method, frequency domain as a check.

- **Main identification, time domain (L2d)**
  - **ks and bs:** ring-down test (free decay), logarithmic decrement → ζ and ωn → ks = ωn²·ml = 132 N/m (payload mode 2.5 Hz), bs = 2ζωn·ml (very small, 0.0048 Ns/m).
    - Figures: bs_ringdown.png, bs.png.
  - **Gain:** step response against the model. An early step test suggested only 0.66 of the Table 1 gain. Later rig data (below) corrected this to 0.99, i.e. Table 1 is right (input gain ≈ 1).
- **Check, frequency domain (L2d, Bode)**
  - A chirp is a sine whose frequency rises slowly, so one run gives the whole Bode plot. The lecture applies one sine at a time; the chirp is the same idea in a single run.
  - Measured in closed loop: the actuator integrates (voltage gives speed, not position), so in open loop a sine makes it drift off the stroke. The plant response is computed as (chirp → X) / (chirp → U).
  - Bode plot of the measurement next to the model (magnitude and phase).
  - Result: the phase at 5–12 Hz fits better with τm ≈ 18 ms (error −4° to 0°) than with the 31 ms that Table 1 implies (+12° to +16°). The coherence is low (0.27–0.34), so this only weakly favours 18 ms.
  - Where the 31 ms comes from: τm = Me·R/(Kf·Ke) with Me = ma + η·Jm·(2π/l)² = 28.7 kg (the motor inertia dominates through the fine screw lead).
  - We design on τm = 18 ms. It is the only Table 1 value we effectively change, and since it is not pinned down exactly the controller is checked over 12–31 ms (section 4).
  - Figures: bode_chirp.png (3–20 Hz; below 3 Hz the loop rejects the chirp, coherence ≈ 0), plant_model.png.
- **Validation against rig behaviour:**
  - Step response against the model (validate_last_run.png).
  - With input gain 0.99 the model predicts the near-instability of the first controller (v1): gain margin about 2.2 dB, oscillation at 5.4–6.5 Hz depending on τm (rig: 6.0–6.25 Hz). It also predicts that the "soft" gain set goes unstable with a few ms of extra delay (run C).
  - This is the argument for trusting the model. Correcting the gain from 0.66 to 0.99 was what made the model match the rig, not the time constant.
- **What the model does not capture:** driver dead band and stiction (driver_map.png).
  - Treated as model uncertainty and handled by integral action, not modelled (outside the course).
- Uncertainty range used for robustness checks: input gain 0.66–1.32, τm 12–31 ms, η down to 0.66 (model η = 1), +5 ms delay.

## 4. Controller design (3 pages)
- **Full-state feedback by LQR (L3g)**
  - Why LQR and not pole placement: there are 6–7 states and it is unclear where to put all the poles. LQR trades error against voltage directly, and Bryson's rule gives the weights a physical meaning.
  - Bryson weights table: i_max 5 A, y_max 25 mm (stroke), ẏ_max 0.15 m/s, x_max 8 mm, ẋ_max 20 mm/s, integral weight, u_max 5 V.
- **Integral action (L3d, augmented state)**
  - Ai = [A 0; −C 0]. Gives zero steady-state error despite the gain error, the real η < 1, bias and load.
  - Why not a prefilter gain N alone: N = 1/dcgain needs an exact model. Our gain estimates ranged from 0.66 to 0.99, and η < 1 is unknown.
- **Anti-windup:** the integrator is frozen while the voltage is saturated.
  This is a small, standard extension; mention it in one line.
- **Choosing between gain sets:**
  - v1 rang at 6 Hz on the rig. The identified model explained it (gain margin 2.2 dB).
  - The v3 selection rule: stable over the whole uncertainty range, ts ≤ 2 s, observer ≥ 2× faster.
  - Margins table: v3a GM 7.6 dB, PM 39°, minimum ζ 0.17 over the uncertainty cases.
  - Including the Table 1 time constant: with τm = 31 ms v3a has GM 7.8 dB and ζ 0.25 (0.16 with +5 ms delay), so the result does not depend on 18 vs 31 ms.

## 5. Observer design (1½ pages)
- Only x is measured, so i, y, ẏ and ẋ must be estimated.
- **Kalman filter (L3h), LQG = LQR + Kalman (separation principle, L3f).**
  - Why Kalman and not pole placement: the noise levels are known physical quantities. Sensor noise 22 µm (measured); process noise = voltage uncertainty plus a 1 N push.
- Check against L3e: observer poles 5.3× faster than the dominant controller poles.
- Discretized at Ts = 0.1 ms (10 kHz Speedgoat rate), as in the Quanser AERO example.

## 6. Simulation (1–2 pages)
- Simulink test model (Controller_test.slx). The controller block is the same as in the real-time model.
- Results for both cases (15→5, 20→5) and a 1 N push, with input gain 0.66, 0.99 (identified) and 1.32 to show robustness.
- Figure: sim_final.png (position for all three gains, voltage for 0.99).

## 7. Real-time implementation (1 page)
- Project_IOinterface.slx left untouched. The controller is generated by a script (build_controller_model.m), so the model can be rebuilt from scratch.
- Figures: block_diagram.png (LQG structure: prefilter, integrator, K_e, K, Kalman observer, bias, limit) and simulink_controller.png (the controller subsystem as built).
- Two small additions found during rig testing:
  - **Reference prefilter** 1/(0.3s + 1)²: smooths the step. It is outside the loop, so the margins do not change. Up-step overshoot dropped from about 20 % to 12 %, and the ±5 V bursts on steps went away.
  - **Start at rest:** the observer, integrator and prefilter start at the payload's measured rest position (1.6 mm). This removed the ±5 V kick at start-up.

## 8. Experimental results (3 pages)
- Figure: final_rig_runs.png (15→5, 20→5, push: X, reference, U).
- Table: requirement against result.

  | Requirement | Result |
  |---|---|
  | Steady-state error | Mean error over the last 2 s of each hold: −0.05 to +0.14 mm (one wander dip −0.5 mm) |
  | Same controller for both cases | Yes, no re-tuning |
  | \|v\| ≤ 5 V | At the limit 0–0.5 % of the time |
  | Stroke 0–25 mm | Yes (one push release −0.3 mm) |
  | Push | Held on the reference while pushed, recovers in about 1 s |

- Before/after table: v3a → + prefilter → final (overshoot, saturation, start-up). Figure: before_after.png.
- Push test: the release spike ≈ F/ks (1 N / 132 N/m ≈ 7.6 mm). That is physics: the integrator has stretched the spring.
- The video file is referenced here.

## 9. Discussion: limitations (1–1½ pages)
- **±1 mm hold wander and 25–33 % down-step overshoot: actuator stiction.**
  - Evidence: video tracking of the actuator next to the voltage log. The actuator stays stuck until about −0.8 V, then jumps.
  - The measured actuator motion pushed through the spring model reproduces the logged payload motion (correlation 0.78 over a 4.4 s hold in wander_spring.png; 0.88–0.98 over shorter windows).
  - The wander is the same for four different controllers, so the controller does not cause it.
  - Figures: wander_spring.png, down_step_stiction.png (actuator moves in stick-slip steps while the voltage goes to about −0.6 V).
- What was tried and did not help: dither, slower/faster gains. One line each.
- What would help (outside the course): friction compensation, a better actuator driver.

## 10. Conclusion (½ page)
- LQG with integral action meets the specs on the real rig. The remaining errors come from the hardware, and we explain them with evidence.

## Appendix
- Parameter table (given and identified).
- File list: how to run (setup_project → build_controller_model → slbuild → load/start).
- Gain matrices K, Ke, L.

---

## Oral exam: likely questions, one-line answers
- Why LQR? Bryson's rule gives weights with physical meaning, and the trade-off against voltage is explicit.
- Why Kalman? The noise is measured, so the observer gain follows from the noise instead of from guessed poles.
- Why integral action? The gain is uncertain (estimates 0.66–0.99), the real η is below the modelled 1.0 by an unknown amount, and there is a holding bias. The integrator removes the steady-state error anyway.
- Why deviation states? Gravity drops out, and the holding voltage is the equilibrium input.
- Why does the prefilter not change stability? It sits outside the feedback loop.
- Why is there overshoot going down? Stiction: video evidence, not a controller problem.
- What does the observer estimate? i, y, ẏ, ẋ and the lagged sensor state, from x and the applied voltage.
- Is the chirp in the curriculum? L2d identifies from sinusoid responses on a Bode plot; a chirp is the same sines swept in one run. Closed loop because the actuator integrates and would drift off the stroke in open loop.
- Why not the Table 1 time constant (31 ms)? The chirp phase weakly favours 18 ms (low coherence). We checked both: the controller is well damped for 12–31 ms.
