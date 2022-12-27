# ELEC522-ADVANCED-VLSI-DESIGN_Assignments
Rice University, Fall 2022 ELEC 522 - ADVANCED VLSI DESIGN Course Assignments

![Xilinx](https://www.xilinx.com/content/dam/xilinx/imgs/press/media-kits/corporate/xilinx-logo.png)

## Getting Started
Download following software for those project:
`Vitis Model Composer`
`Vitis HLS`
`Vivado`
`Xilinx Vitis`

## Folder Arrangement Explanation:

I didn't organize Project1-2 well, but Project3-6 will be organize as follow:

In the Project3, we need to complete Matrix Multiplication Vitis HLS, and using Model Composer to compare the results, so here I organize the folder as `Model_Composer` and `Vitis_HLS_code`, you can run the Model Composer part in the folder, but if you want to run the HLS C++ code, you will need to creat a Vitis HLS project, then import the C++ code into it. **Here's the folder location for my Project3** [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project3/project3_v1)

In Project 4, we need to implement CORDIC algorithm using Vitis HLS, and export it into Model Composer using Vitis HLS block, and generate and verify with hardware Co-Sim in Model Composer on the Zedboard, also generate another IP catalog for Vivado, then export hardware (.xsa) from Vivado into Vitis IDE tools, finally write another C++ code for ARM core, and build it run on the ZedBoard, verify that you can compute proper sines, cosines, and inverse tangents. So here I organize the folder as `Model_Composer`, `fpga_hls`, `Vivado`, and `arm_vitis`, you can follow the steps in the lecture to complete the project sequentially, so I won't introduce you here. **Here's the folder location for my Project4** [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project4/project4)

In Project5 you have to design 4x4 Matrix QR-decomposition based on the CORDIC algorithm, the CORDIC part complete in the Project4, so we need to copy the previous Vitis HLS C++ code to this project, after complete the QR-decomposition in Model Composer, you need to generate Vivado IP catalog, then do the same steps from Project4 to the Vitis IDE tools, then also write a C++ code for ARM core, built and run on Zedboard. I organize the folder as `Model_Composer`, `fpga_hls`, `Vitis_HLS`, `Vivado`, `arm_vitis`, and `Vitis`, for this project, I compressed my CORDIC algorithm Vitis HLS part and Arm core part into .zip file and placed it in `Vitis_HLS` and `Vitis` accordingly. You can try to unzip it and try to run it, but I can't guarantee that it will run 100% on your equipment. You can try the projects provided by other students and see if they work successfully. **Here's the folder location for my Project5** [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project5/project5_final)

In the last project, Project 6 will integrate all projects to complete the linear solver system to solve the equation Ax = b, where A matrix is a 4x4 matrix and x vector is a 4x1 vector, this project will need to design another `back-substitution` function, and you will need to complete linear solver system in Model Composer and Vitis HLS, then analyze and compare the throughput and resource utilization of the individual results. I organize this project's folder same as Project5, but it will have a little bit difference between it, the file name end with "_MC" means for the Model Composer part, and the file name end with "_LinearSolver" means using Vitis HLS to complete linear solver system. You can still try to unzip all the files and try to run it, but I can't guarantee that it will run 100% on your equipment. You can try the projects provided by other students and see if they work successfully. **Here's the folder location for my Project6** [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project6)

**---If you like this project, or find these files helpful, don't forget to give me a star, your star is what keeps me running GitHub! Thank you!---**

## Acknowledgements
Many thanks to the following students for providing their assignments for reference:

`@Aedan Cullen`, `@Jason Zhang` from CS department, and `@Antonio Mendoza Gonzales`, `@Cameron Kramr`, `@Karan Venaik`, `@Juan Garza`, `@Sixu Li`, `@Jie Gao`, `@Yufei Gu` from ECE department.

## Project 1:
**Project 1- Xilinx Vitis Model Composer / Nvidia CUDA Tutorial Assignment**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project1)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project1/ELEC_522_Proj_1_Sysgen_CUDA_Intro.pdf)

## Project 2:
**Project 2- Xilinx FPGA Model Composer Systolic for Matrix Multiplication**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project2)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project2/ELEC_522_Proj_2_Matrix_Mult.pdf)

## Project 3:
**Project 3- Using Vitis HLS to Implement Matrix Multiplication**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project3)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project3/ELEC_522_Proj_3_VitisHLS_Matrix_Mult.pdf)

## Project 4:
**Project 4- Using VitisHLS to implement a CORDIC module on Zynq**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project4)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project4/ELEC_522_Proj_4_VitisHLS_CORDIC.pdf)

## Project 5:
**Project5- QR Decomposition using CORDIC arithmetic for a 4 x 4 matrix**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project5)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project5/ELEC_522_Proj_5_QRD.pdf)

## Project 6:
**Project 6- 4 x 4 Linear System Solver with ARM Core and CORDIC QRD and MatrixMultiplication Accelerator Integration**: [this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/tree/main/Project6)

Project Goals:[this repository](https://github.com/PiscesLin/Rice_ELEC522-ADVANCED-VLSI-DESIGN_Assignments/blob/main/Project6/ELEC_522_Proj_6_Array.pdf)



## License
This project is licensed under Rice University

![Rice_University](https://brand.rice.edu/sites/g/files/bxs2591/files/2019-08/190308_Rice_Mechanical_Brand_Standards_Logos-9.png)
