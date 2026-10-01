set(SOURCES
	CB_m0.cpp
	CL_m1.cpp
	LB_3p3_1p3.cpp
	subdiv_0_3p1_1p1.cpp
	subdiv_1_3p1_1p1.cpp
	subdiv_0_3p3_1p3.cpp
	subdiv_1_3p3_1p3.cpp
	P2TetCGVR2.cpp
)

target_sources(miso PRIVATE ${SOURCES})
