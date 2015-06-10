all:
	g++ gen_rsa_keys.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o gen_rsa_keys
	g++ rsa.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o rsa
