# transientflow-1d

**transientflow-1d** is a C++-based simulation tool developed to model **1D unsteady fluid flow** through a channel using fundamental conservation laws. It applies the **Finite Volume Method (FVM)** with time-only discretization, solving governing equations for both **compressible and incompressible flows** under the influence of heat transfer and frictional forces.

## 🔬 Key Features

- Solves 1D transient fluid dynamics problems
- Handles both compressible and incompressible regimes
- Incorporates frictional and thermal source terms
- Based on conservation of mass, momentum, and energy
- Efficient single control-volume time-stepping approach
- Suitable for research, engineering applications, and learning

## 📘 Governing Equations

The simulation is governed by the following:

- **Continuity Equation:**  
  $$ \frac{{\partial \rho}}{{\partial t}} + \frac{{\partial (\rho u)}}{{\partial x}} = 0 $$

- **Momentum Equation:**  
  $$ \frac{{\partial (\rho u)}}{{\partial t}} + \frac{{\partial (\rho u^2)}}{{\partial x}} = -\frac{{\partial p}}{{\partial x}} + \dot{F}_{fr} $$

- **Energy Equation (Ideal Gas):**  
  $$ \frac{{\partial (\rho C_v T)}}{{\partial t}} + \frac{{\partial (\rho C_v T u)}}{{\partial x}} = -p \frac{{\partial u}}{{\partial x}} + \frac{{\partial}}{{\partial x}}\left(k \frac{{\partial T}}{{\partial x}}\right) + \dot{F}_{fr} u $$

## 📥 Input Parameters

Defined at the west face (inlet):
- `p1` – Static pressure
- `u1` – Velocity
- `h01` or `T1` – Total enthalpy or temperature
- `Ffr` – Frictional force
- `Q` – Heat input

Computed at the east face (outlet):
- `p2`, `u2`, `h02`

## ⚙️ Simulation Workflow

1. Initialize physical properties and boundary conditions
2. Loop through time steps (`Δt`)
3. Sequentially solve:
   - Continuity equation
   - Momentum equation
   - Energy equation
4. Update variables and store results

## 🧰 Technologies

- Language: **C++**
- Methodology: **Finite Volume Method (FVM)**
- Model: **1 control volume, transient-only discretization**

## 🧑‍💻 Author

Created by **Duc Phi Ngo**, a CFD/FEA engineer with a strong background in simulation and software engineering. This project demonstrates the integration of theoretical modeling and computational implementation for real-world fluid systems.

---

For detailed derivations and case studies, please refer to the full project documentation or contact the author.
