
./test/test_queue:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 c9 2f 00 00 	mov    0x2fc9(%rip),%rax        # 3fd8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 fa 2e 00 00    	push   0x2efa(%rip)        # 3f20 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 fb 2e 00 00 	bnd jmp *0x2efb(%rip)        # 3f28 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	push   $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	push   $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	push   $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmp 1020 <_init+0x20>
    108f:	90                   	nop
    1090:	f3 0f 1e fa          	endbr64 
    1094:	68 06 00 00 00       	push   $0x6
    1099:	f2 e9 81 ff ff ff    	bnd jmp 1020 <_init+0x20>
    109f:	90                   	nop
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	68 07 00 00 00       	push   $0x7
    10a9:	f2 e9 71 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10af:	90                   	nop
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	68 08 00 00 00       	push   $0x8
    10b9:	f2 e9 61 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10bf:	90                   	nop
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	68 09 00 00 00       	push   $0x9
    10c9:	f2 e9 51 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10cf:	90                   	nop
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	68 0a 00 00 00       	push   $0xa
    10d9:	f2 e9 41 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10df:	90                   	nop
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	68 0b 00 00 00       	push   $0xb
    10e9:	f2 e9 31 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10ef:	90                   	nop
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	68 0c 00 00 00       	push   $0xc
    10f9:	f2 e9 21 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10ff:	90                   	nop
    1100:	f3 0f 1e fa          	endbr64 
    1104:	68 0d 00 00 00       	push   $0xd
    1109:	f2 e9 11 ff ff ff    	bnd jmp 1020 <_init+0x20>
    110f:	90                   	nop
    1110:	f3 0f 1e fa          	endbr64 
    1114:	68 0e 00 00 00       	push   $0xe
    1119:	f2 e9 01 ff ff ff    	bnd jmp 1020 <_init+0x20>
    111f:	90                   	nop

Disassembly of section .plt.got:

0000000000001120 <__cxa_finalize@plt>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	f2 ff 25 7d 2e 00 00 	bnd jmp *0x2e7d(%rip)        # 3fa8 <__cxa_finalize@GLIBC_2.2.5>
    112b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001130 <_Znam@plt>:
    1130:	f3 0f 1e fa          	endbr64 
    1134:	f2 ff 25 f5 2d 00 00 	bnd jmp *0x2df5(%rip)        # 3f30 <_Znam@GLIBCXX_3.4>
    113b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001140 <_ZNSt14overflow_errorC1EPKc@plt>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	f2 ff 25 ed 2d 00 00 	bnd jmp *0x2ded(%rip)        # 3f38 <_ZNSt14overflow_errorC1EPKc@GLIBCXX_3.4.21>
    114b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001150 <__cxa_allocate_exception@plt>:
    1150:	f3 0f 1e fa          	endbr64 
    1154:	f2 ff 25 e5 2d 00 00 	bnd jmp *0x2de5(%rip)        # 3f40 <__cxa_allocate_exception@CXXABI_1.3>
    115b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001160 <__cxa_free_exception@plt>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	f2 ff 25 dd 2d 00 00 	bnd jmp *0x2ddd(%rip)        # 3f48 <__cxa_free_exception@CXXABI_1.3>
    116b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001170 <__cxa_atexit@plt>:
    1170:	f3 0f 1e fa          	endbr64 
    1174:	f2 ff 25 d5 2d 00 00 	bnd jmp *0x2dd5(%rip)        # 3f50 <__cxa_atexit@GLIBC_2.2.5>
    117b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001180 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	f2 ff 25 cd 2d 00 00 	bnd jmp *0x2dcd(%rip)        # 3f58 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4>
    118b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001190 <_ZNSolsEPFRSoS_E@plt>:
    1190:	f3 0f 1e fa          	endbr64 
    1194:	f2 ff 25 c5 2d 00 00 	bnd jmp *0x2dc5(%rip)        # 3f60 <_ZNSolsEPFRSoS_E@GLIBCXX_3.4>
    119b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011a0 <__stack_chk_fail@plt>:
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	f2 ff 25 bd 2d 00 00 	bnd jmp *0x2dbd(%rip)        # 3f68 <__stack_chk_fail@GLIBC_2.4>
    11ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011b0 <__cxa_throw_bad_array_new_length@plt>:
    11b0:	f3 0f 1e fa          	endbr64 
    11b4:	f2 ff 25 b5 2d 00 00 	bnd jmp *0x2db5(%rip)        # 3f70 <__cxa_throw_bad_array_new_length@CXXABI_1.3.8>
    11bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011c0 <_ZNSt8ios_base4InitC1Ev@plt>:
    11c0:	f3 0f 1e fa          	endbr64 
    11c4:	f2 ff 25 ad 2d 00 00 	bnd jmp *0x2dad(%rip)        # 3f78 <_ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4>
    11cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011d0 <__cxa_throw@plt>:
    11d0:	f3 0f 1e fa          	endbr64 
    11d4:	f2 ff 25 a5 2d 00 00 	bnd jmp *0x2da5(%rip)        # 3f80 <__cxa_throw@CXXABI_1.3>
    11db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011e0 <_ZNSolsEi@plt>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	f2 ff 25 9d 2d 00 00 	bnd jmp *0x2d9d(%rip)        # 3f88 <_ZNSolsEi@GLIBCXX_3.4>
    11eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000011f0 <_Unwind_Resume@plt>:
    11f0:	f3 0f 1e fa          	endbr64 
    11f4:	f2 ff 25 95 2d 00 00 	bnd jmp *0x2d95(%rip)        # 3f90 <_Unwind_Resume@GCC_3.0>
    11fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001200 <_ZNSt16invalid_argumentC1EPKc@plt>:
    1200:	f3 0f 1e fa          	endbr64 
    1204:	f2 ff 25 8d 2d 00 00 	bnd jmp *0x2d8d(%rip)        # 3f98 <_ZNSt16invalid_argumentC1EPKc@GLIBCXX_3.4.21>
    120b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001210 <_ZNSt15underflow_errorC1EPKc@plt>:
    1210:	f3 0f 1e fa          	endbr64 
    1214:	f2 ff 25 85 2d 00 00 	bnd jmp *0x2d85(%rip)        # 3fa0 <_ZNSt15underflow_errorC1EPKc@GLIBCXX_3.4.21>
    121b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001220 <_start>:
    1220:	f3 0f 1e fa          	endbr64 
    1224:	31 ed                	xor    %ebp,%ebp
    1226:	49 89 d1             	mov    %rdx,%r9
    1229:	5e                   	pop    %rsi
    122a:	48 89 e2             	mov    %rsp,%rdx
    122d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1231:	50                   	push   %rax
    1232:	54                   	push   %rsp
    1233:	45 31 c0             	xor    %r8d,%r8d
    1236:	31 c9                	xor    %ecx,%ecx
    1238:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1309 <main>
    123f:	ff 15 7b 2d 00 00    	call   *0x2d7b(%rip)        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1245:	f4                   	hlt    
    1246:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    124d:	00 00 00 

0000000000001250 <deregister_tm_clones>:
    1250:	48 8d 3d c1 2d 00 00 	lea    0x2dc1(%rip),%rdi        # 4018 <__TMC_END__>
    1257:	48 8d 05 ba 2d 00 00 	lea    0x2dba(%rip),%rax        # 4018 <__TMC_END__>
    125e:	48 39 f8             	cmp    %rdi,%rax
    1261:	74 15                	je     1278 <deregister_tm_clones+0x28>
    1263:	48 8b 05 66 2d 00 00 	mov    0x2d66(%rip),%rax        # 3fd0 <_ITM_deregisterTMCloneTable@Base>
    126a:	48 85 c0             	test   %rax,%rax
    126d:	74 09                	je     1278 <deregister_tm_clones+0x28>
    126f:	ff e0                	jmp    *%rax
    1271:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1278:	c3                   	ret    
    1279:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001280 <register_tm_clones>:
    1280:	48 8d 3d 91 2d 00 00 	lea    0x2d91(%rip),%rdi        # 4018 <__TMC_END__>
    1287:	48 8d 35 8a 2d 00 00 	lea    0x2d8a(%rip),%rsi        # 4018 <__TMC_END__>
    128e:	48 29 fe             	sub    %rdi,%rsi
    1291:	48 89 f0             	mov    %rsi,%rax
    1294:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1298:	48 c1 f8 03          	sar    $0x3,%rax
    129c:	48 01 c6             	add    %rax,%rsi
    129f:	48 d1 fe             	sar    %rsi
    12a2:	74 14                	je     12b8 <register_tm_clones+0x38>
    12a4:	48 8b 05 35 2d 00 00 	mov    0x2d35(%rip),%rax        # 3fe0 <_ITM_registerTMCloneTable@Base>
    12ab:	48 85 c0             	test   %rax,%rax
    12ae:	74 08                	je     12b8 <register_tm_clones+0x38>
    12b0:	ff e0                	jmp    *%rax
    12b2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    12b8:	c3                   	ret    
    12b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000012c0 <__do_global_dtors_aux>:
    12c0:	f3 0f 1e fa          	endbr64 
    12c4:	80 3d 85 2e 00 00 00 	cmpb   $0x0,0x2e85(%rip)        # 4150 <completed.0>
    12cb:	75 2b                	jne    12f8 <__do_global_dtors_aux+0x38>
    12cd:	55                   	push   %rbp
    12ce:	48 83 3d d2 2c 00 00 	cmpq   $0x0,0x2cd2(%rip)        # 3fa8 <__cxa_finalize@GLIBC_2.2.5>
    12d5:	00 
    12d6:	48 89 e5             	mov    %rsp,%rbp
    12d9:	74 0c                	je     12e7 <__do_global_dtors_aux+0x27>
    12db:	48 8b 3d 26 2d 00 00 	mov    0x2d26(%rip),%rdi        # 4008 <__dso_handle>
    12e2:	e8 39 fe ff ff       	call   1120 <__cxa_finalize@plt>
    12e7:	e8 64 ff ff ff       	call   1250 <deregister_tm_clones>
    12ec:	c6 05 5d 2e 00 00 01 	movb   $0x1,0x2e5d(%rip)        # 4150 <completed.0>
    12f3:	5d                   	pop    %rbp
    12f4:	c3                   	ret    
    12f5:	0f 1f 00             	nopl   (%rax)
    12f8:	c3                   	ret    
    12f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001300 <frame_dummy>:
    1300:	f3 0f 1e fa          	endbr64 
    1304:	e9 77 ff ff ff       	jmp    1280 <register_tm_clones>

0000000000001309 <main>:
    1309:	f3 0f 1e fa          	endbr64 
    130d:	55                   	push   %rbp
    130e:	48 89 e5             	mov    %rsp,%rbp
    1311:	48 83 ec 40          	sub    $0x40,%rsp
    1315:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    131c:	00 00 
    131e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1322:	31 c0                	xor    %eax,%eax
    1324:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    1328:	be 0a 00 00 00       	mov    $0xa,%esi
    132d:	48 89 c7             	mov    %rax,%rdi
    1330:	e8 d1 00 00 00       	call   1406 <_ZN5QueueIiEC1Em>
    1335:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    1339:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    133d:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1341:	be 01 00 00 00       	mov    $0x1,%esi
    1346:	48 89 c7             	mov    %rax,%rdi
    1349:	e8 90 01 00 00       	call   14de <_ZN5QueueIiE10appendLeftEi>
    134e:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1352:	be 02 00 00 00       	mov    $0x2,%esi
    1357:	48 89 c7             	mov    %rax,%rdi
    135a:	e8 7f 01 00 00       	call   14de <_ZN5QueueIiE10appendLeftEi>
    135f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1363:	be 03 00 00 00       	mov    $0x3,%esi
    1368:	48 89 c7             	mov    %rax,%rdi
    136b:	e8 6e 01 00 00       	call   14de <_ZN5QueueIiE10appendLeftEi>
    1370:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1374:	48 89 c7             	mov    %rax,%rdi
    1377:	e8 32 02 00 00       	call   15ae <_ZNK5QueueIiE12displayQueueEv>
    137c:	b8 00 00 00 00       	mov    $0x0,%eax
    1381:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    1385:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    138c:	00 00 
    138e:	74 05                	je     1395 <main+0x8c>
    1390:	e8 0b fe ff ff       	call   11a0 <__stack_chk_fail@plt>
    1395:	c9                   	leave  
    1396:	c3                   	ret    

0000000000001397 <_Z41__static_initialization_and_destruction_0ii>:
    1397:	f3 0f 1e fa          	endbr64 
    139b:	55                   	push   %rbp
    139c:	48 89 e5             	mov    %rsp,%rbp
    139f:	48 83 ec 10          	sub    $0x10,%rsp
    13a3:	89 7d fc             	mov    %edi,-0x4(%rbp)
    13a6:	89 75 f8             	mov    %esi,-0x8(%rbp)
    13a9:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    13ad:	75 3b                	jne    13ea <_Z41__static_initialization_and_destruction_0ii+0x53>
    13af:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    13b6:	75 32                	jne    13ea <_Z41__static_initialization_and_destruction_0ii+0x53>
    13b8:	48 8d 05 92 2d 00 00 	lea    0x2d92(%rip),%rax        # 4151 <_ZStL8__ioinit>
    13bf:	48 89 c7             	mov    %rax,%rdi
    13c2:	e8 f9 fd ff ff       	call   11c0 <_ZNSt8ios_base4InitC1Ev@plt>
    13c7:	48 8d 05 3a 2c 00 00 	lea    0x2c3a(%rip),%rax        # 4008 <__dso_handle>
    13ce:	48 89 c2             	mov    %rax,%rdx
    13d1:	48 8d 05 79 2d 00 00 	lea    0x2d79(%rip),%rax        # 4151 <_ZStL8__ioinit>
    13d8:	48 89 c6             	mov    %rax,%rsi
    13db:	48 8b 05 0e 2c 00 00 	mov    0x2c0e(%rip),%rax        # 3ff0 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    13e2:	48 89 c7             	mov    %rax,%rdi
    13e5:	e8 86 fd ff ff       	call   1170 <__cxa_atexit@plt>
    13ea:	90                   	nop
    13eb:	c9                   	leave  
    13ec:	c3                   	ret    

00000000000013ed <_GLOBAL__sub_I_main>:
    13ed:	f3 0f 1e fa          	endbr64 
    13f1:	55                   	push   %rbp
    13f2:	48 89 e5             	mov    %rsp,%rbp
    13f5:	be ff ff 00 00       	mov    $0xffff,%esi
    13fa:	bf 01 00 00 00       	mov    $0x1,%edi
    13ff:	e8 93 ff ff ff       	call   1397 <_Z41__static_initialization_and_destruction_0ii>
    1404:	5d                   	pop    %rbp
    1405:	c3                   	ret    

0000000000001406 <_ZN5QueueIiEC1Em>:
    1406:	f3 0f 1e fa          	endbr64 
    140a:	55                   	push   %rbp
    140b:	48 89 e5             	mov    %rsp,%rbp
    140e:	41 54                	push   %r12
    1410:	53                   	push   %rbx
    1411:	48 83 ec 10          	sub    $0x10,%rsp
    1415:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1419:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    141d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1421:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    1425:	48 89 50 18          	mov    %rdx,0x18(%rax)
    1429:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
    142e:	75 3b                	jne    146b <_ZN5QueueIiEC1Em+0x65>
    1430:	bf 10 00 00 00       	mov    $0x10,%edi
    1435:	e8 16 fd ff ff       	call   1150 <__cxa_allocate_exception@plt>
    143a:	48 89 c3             	mov    %rax,%rbx
    143d:	48 8d 05 c0 0b 00 00 	lea    0xbc0(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1444:	48 89 c6             	mov    %rax,%rsi
    1447:	48 89 df             	mov    %rbx,%rdi
    144a:	e8 b1 fd ff ff       	call   1200 <_ZNSt16invalid_argumentC1EPKc@plt>
    144f:	48 8b 05 72 2b 00 00 	mov    0x2b72(%rip),%rax        # 3fc8 <_ZNSt16invalid_argumentD1Ev@GLIBCXX_3.4>
    1456:	48 89 c2             	mov    %rax,%rdx
    1459:	48 8d 05 90 28 00 00 	lea    0x2890(%rip),%rax        # 3cf0 <_ZTISt16invalid_argument@GLIBCXX_3.4>
    1460:	48 89 c6             	mov    %rax,%rsi
    1463:	48 89 df             	mov    %rbx,%rdi
    1466:	e8 65 fd ff ff       	call   11d0 <__cxa_throw@plt>
    146b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    146f:	48 83 c0 01          	add    $0x1,%rax
    1473:	48 ba fe ff ff ff ff 	movabs $0x1ffffffffffffffe,%rdx
    147a:	ff ff 1f 
    147d:	48 39 d0             	cmp    %rdx,%rax
    1480:	77 34                	ja     14b6 <_ZN5QueueIiEC1Em+0xb0>
    1482:	48 c1 e0 02          	shl    $0x2,%rax
    1486:	48 89 c7             	mov    %rax,%rdi
    1489:	e8 a2 fc ff ff       	call   1130 <_Znam@plt>
    148e:	48 89 c2             	mov    %rax,%rdx
    1491:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1495:	48 89 10             	mov    %rdx,(%rax)
    1498:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    149c:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
    14a3:	00 
    14a4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    14a8:	48 8b 50 10          	mov    0x10(%rax),%rdx
    14ac:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    14b0:	48 89 50 08          	mov    %rdx,0x8(%rax)
    14b4:	eb 1f                	jmp    14d5 <_ZN5QueueIiEC1Em+0xcf>
    14b6:	e8 f5 fc ff ff       	call   11b0 <__cxa_throw_bad_array_new_length@plt>
    14bb:	f3 0f 1e fa          	endbr64 
    14bf:	49 89 c4             	mov    %rax,%r12
    14c2:	48 89 df             	mov    %rbx,%rdi
    14c5:	e8 96 fc ff ff       	call   1160 <__cxa_free_exception@plt>
    14ca:	4c 89 e0             	mov    %r12,%rax
    14cd:	48 89 c7             	mov    %rax,%rdi
    14d0:	e8 1b fd ff ff       	call   11f0 <_Unwind_Resume@plt>
    14d5:	48 83 c4 10          	add    $0x10,%rsp
    14d9:	5b                   	pop    %rbx
    14da:	41 5c                	pop    %r12
    14dc:	5d                   	pop    %rbp
    14dd:	c3                   	ret    

00000000000014de <_ZN5QueueIiE10appendLeftEi>:
    14de:	f3 0f 1e fa          	endbr64 
    14e2:	55                   	push   %rbp
    14e3:	48 89 e5             	mov    %rsp,%rbp
    14e6:	41 54                	push   %r12
    14e8:	53                   	push   %rbx
    14e9:	48 83 ec 20          	sub    $0x20,%rsp
    14ed:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    14f1:	89 75 d4             	mov    %esi,-0x2c(%rbp)
    14f4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14f8:	48 89 c7             	mov    %rax,%rdi
    14fb:	e8 f8 01 00 00       	call   16f8 <_ZNK5QueueIiE6isFullEv>
    1500:	84 c0                	test   %al,%al
    1502:	74 3b                	je     153f <_ZN5QueueIiE10appendLeftEi+0x61>
    1504:	bf 10 00 00 00       	mov    $0x10,%edi
    1509:	e8 42 fc ff ff       	call   1150 <__cxa_allocate_exception@plt>
    150e:	48 89 c3             	mov    %rax,%rbx
    1511:	48 8d 05 07 0b 00 00 	lea    0xb07(%rip),%rax        # 201f <_IO_stdin_used+0x1f>
    1518:	48 89 c6             	mov    %rax,%rsi
    151b:	48 89 df             	mov    %rbx,%rdi
    151e:	e8 1d fc ff ff       	call   1140 <_ZNSt14overflow_errorC1EPKc@plt>
    1523:	48 8b 05 8e 2a 00 00 	mov    0x2a8e(%rip),%rax        # 3fb8 <_ZNSt14overflow_errorD1Ev@GLIBCXX_3.4>
    152a:	48 89 c2             	mov    %rax,%rdx
    152d:	48 8d 05 8c 27 00 00 	lea    0x278c(%rip),%rax        # 3cc0 <_ZTISt14overflow_error@GLIBCXX_3.4>
    1534:	48 89 c6             	mov    %rax,%rsi
    1537:	48 89 df             	mov    %rbx,%rdi
    153a:	e8 91 fc ff ff       	call   11d0 <__cxa_throw@plt>
    153f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1543:	48 8b 40 08          	mov    0x8(%rax),%rax
    1547:	48 85 c0             	test   %rax,%rax
    154a:	75 0a                	jne    1556 <_ZN5QueueIiE10appendLeftEi+0x78>
    154c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1550:	48 8b 40 18          	mov    0x18(%rax),%rax
    1554:	eb 0c                	jmp    1562 <_ZN5QueueIiE10appendLeftEi+0x84>
    1556:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    155a:	48 8b 40 08          	mov    0x8(%rax),%rax
    155e:	48 83 e8 01          	sub    $0x1,%rax
    1562:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1566:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    156a:	48 8b 10             	mov    (%rax),%rdx
    156d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1571:	48 c1 e0 02          	shl    $0x2,%rax
    1575:	48 01 c2             	add    %rax,%rdx
    1578:	8b 45 d4             	mov    -0x2c(%rbp),%eax
    157b:	89 02                	mov    %eax,(%rdx)
    157d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1581:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    1585:	48 89 50 08          	mov    %rdx,0x8(%rax)
    1589:	eb 1a                	jmp    15a5 <_ZN5QueueIiE10appendLeftEi+0xc7>
    158b:	f3 0f 1e fa          	endbr64 
    158f:	49 89 c4             	mov    %rax,%r12
    1592:	48 89 df             	mov    %rbx,%rdi
    1595:	e8 c6 fb ff ff       	call   1160 <__cxa_free_exception@plt>
    159a:	4c 89 e0             	mov    %r12,%rax
    159d:	48 89 c7             	mov    %rax,%rdi
    15a0:	e8 4b fc ff ff       	call   11f0 <_Unwind_Resume@plt>
    15a5:	48 83 c4 20          	add    $0x20,%rsp
    15a9:	5b                   	pop    %rbx
    15aa:	41 5c                	pop    %r12
    15ac:	5d                   	pop    %rbp
    15ad:	c3                   	ret    

00000000000015ae <_ZNK5QueueIiE12displayQueueEv>:
    15ae:	f3 0f 1e fa          	endbr64 
    15b2:	55                   	push   %rbp
    15b3:	48 89 e5             	mov    %rsp,%rbp
    15b6:	41 54                	push   %r12
    15b8:	53                   	push   %rbx
    15b9:	48 83 ec 30          	sub    $0x30,%rsp
    15bd:	48 89 7d c8          	mov    %rdi,-0x38(%rbp)
    15c1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    15c5:	48 89 c7             	mov    %rax,%rdi
    15c8:	e8 6b 01 00 00       	call   1738 <_ZNK5QueueIiE7isEmptyEv>
    15cd:	84 c0                	test   %al,%al
    15cf:	74 3b                	je     160c <_ZNK5QueueIiE12displayQueueEv+0x5e>
    15d1:	bf 10 00 00 00       	mov    $0x10,%edi
    15d6:	e8 75 fb ff ff       	call   1150 <__cxa_allocate_exception@plt>
    15db:	48 89 c3             	mov    %rax,%rbx
    15de:	48 8d 05 48 0a 00 00 	lea    0xa48(%rip),%rax        # 202d <_IO_stdin_used+0x2d>
    15e5:	48 89 c6             	mov    %rax,%rsi
    15e8:	48 89 df             	mov    %rbx,%rdi
    15eb:	e8 20 fc ff ff       	call   1210 <_ZNSt15underflow_errorC1EPKc@plt>
    15f0:	48 8b 05 f1 29 00 00 	mov    0x29f1(%rip),%rax        # 3fe8 <_ZNSt15underflow_errorD1Ev@GLIBCXX_3.4>
    15f7:	48 89 c2             	mov    %rax,%rdx
    15fa:	48 8d 05 d7 26 00 00 	lea    0x26d7(%rip),%rax        # 3cd8 <_ZTISt15underflow_error@GLIBCXX_3.4>
    1601:	48 89 c6             	mov    %rax,%rsi
    1604:	48 89 df             	mov    %rbx,%rdi
    1607:	e8 c4 fb ff ff       	call   11d0 <__cxa_throw@plt>
    160c:	48 8d 05 29 0a 00 00 	lea    0xa29(%rip),%rax        # 203c <_IO_stdin_used+0x3c>
    1613:	48 89 c6             	mov    %rax,%rsi
    1616:	48 8d 05 23 2a 00 00 	lea    0x2a23(%rip),%rax        # 4040 <_ZSt4cout@GLIBCXX_3.4>
    161d:	48 89 c7             	mov    %rax,%rdi
    1620:	e8 5b fb ff ff       	call   1180 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    1625:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1629:	48 8b 40 10          	mov    0x10(%rax),%rax
    162d:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    1631:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1635:	48 8b 40 18          	mov    0x18(%rax),%rax
    1639:	48 83 c0 01          	add    $0x1,%rax
    163d:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1641:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1645:	48 8b 40 08          	mov    0x8(%rax),%rax
    1649:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    164d:	eb 4f                	jmp    169e <_ZNK5QueueIiE12displayQueueEv+0xf0>
    164f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    1653:	48 8b 10             	mov    (%rax),%rdx
    1656:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    165a:	48 c1 e0 02          	shl    $0x2,%rax
    165e:	48 01 d0             	add    %rdx,%rax
    1661:	8b 00                	mov    (%rax),%eax
    1663:	89 c6                	mov    %eax,%esi
    1665:	48 8d 05 d4 29 00 00 	lea    0x29d4(%rip),%rax        # 4040 <_ZSt4cout@GLIBCXX_3.4>
    166c:	48 89 c7             	mov    %rax,%rdi
    166f:	e8 6c fb ff ff       	call   11e0 <_ZNSolsEi@plt>
    1674:	48 89 c2             	mov    %rax,%rdx
    1677:	48 8d 05 c7 09 00 00 	lea    0x9c7(%rip),%rax        # 2045 <_IO_stdin_used+0x45>
    167e:	48 89 c6             	mov    %rax,%rsi
    1681:	48 89 d7             	mov    %rdx,%rdi
    1684:	e8 f7 fa ff ff       	call   1180 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    1689:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    168d:	48 83 c0 01          	add    $0x1,%rax
    1691:	ba 00 00 00 00       	mov    $0x0,%edx
    1696:	48 f7 75 e8          	divq   -0x18(%rbp)
    169a:	48 89 55 d8          	mov    %rdx,-0x28(%rbp)
    169e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16a2:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
    16a6:	75 a7                	jne    164f <_ZNK5QueueIiE12displayQueueEv+0xa1>
    16a8:	48 8d 05 9b 09 00 00 	lea    0x99b(%rip),%rax        # 204a <_IO_stdin_used+0x4a>
    16af:	48 89 c6             	mov    %rax,%rsi
    16b2:	48 8d 05 87 29 00 00 	lea    0x2987(%rip),%rax        # 4040 <_ZSt4cout@GLIBCXX_3.4>
    16b9:	48 89 c7             	mov    %rax,%rdi
    16bc:	e8 bf fa ff ff       	call   1180 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    16c1:	48 8b 15 e8 28 00 00 	mov    0x28e8(%rip),%rdx        # 3fb0 <_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GLIBCXX_3.4>
    16c8:	48 89 d6             	mov    %rdx,%rsi
    16cb:	48 89 c7             	mov    %rax,%rdi
    16ce:	e8 bd fa ff ff       	call   1190 <_ZNSolsEPFRSoS_E@plt>
    16d3:	eb 1a                	jmp    16ef <_ZNK5QueueIiE12displayQueueEv+0x141>
    16d5:	f3 0f 1e fa          	endbr64 
    16d9:	49 89 c4             	mov    %rax,%r12
    16dc:	48 89 df             	mov    %rbx,%rdi
    16df:	e8 7c fa ff ff       	call   1160 <__cxa_free_exception@plt>
    16e4:	4c 89 e0             	mov    %r12,%rax
    16e7:	48 89 c7             	mov    %rax,%rdi
    16ea:	e8 01 fb ff ff       	call   11f0 <_Unwind_Resume@plt>
    16ef:	48 83 c4 30          	add    $0x30,%rsp
    16f3:	5b                   	pop    %rbx
    16f4:	41 5c                	pop    %r12
    16f6:	5d                   	pop    %rbp
    16f7:	c3                   	ret    

00000000000016f8 <_ZNK5QueueIiE6isFullEv>:
    16f8:	f3 0f 1e fa          	endbr64 
    16fc:	55                   	push   %rbp
    16fd:	48 89 e5             	mov    %rsp,%rbp
    1700:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1704:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1708:	48 8b 40 10          	mov    0x10(%rax),%rax
    170c:	48 8d 50 01          	lea    0x1(%rax),%rdx
    1710:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1714:	48 8b 40 18          	mov    0x18(%rax),%rax
    1718:	48 8d 48 01          	lea    0x1(%rax),%rcx
    171c:	48 89 d0             	mov    %rdx,%rax
    171f:	ba 00 00 00 00       	mov    $0x0,%edx
    1724:	48 f7 f1             	div    %rcx
    1727:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    172b:	48 8b 40 08          	mov    0x8(%rax),%rax
    172f:	48 39 c2             	cmp    %rax,%rdx
    1732:	0f 94 c0             	sete   %al
    1735:	5d                   	pop    %rbp
    1736:	c3                   	ret    
    1737:	90                   	nop

0000000000001738 <_ZNK5QueueIiE7isEmptyEv>:
    1738:	f3 0f 1e fa          	endbr64 
    173c:	55                   	push   %rbp
    173d:	48 89 e5             	mov    %rsp,%rbp
    1740:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1744:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1748:	48 8b 50 08          	mov    0x8(%rax),%rdx
    174c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1750:	48 8b 40 10          	mov    0x10(%rax),%rax
    1754:	48 39 c2             	cmp    %rax,%rdx
    1757:	0f 94 c0             	sete   %al
    175a:	5d                   	pop    %rbp
    175b:	c3                   	ret    

000000000000175c <_Z41__static_initialization_and_destruction_0ii>:
    175c:	f3 0f 1e fa          	endbr64 
    1760:	55                   	push   %rbp
    1761:	48 89 e5             	mov    %rsp,%rbp
    1764:	48 83 ec 10          	sub    $0x10,%rsp
    1768:	89 7d fc             	mov    %edi,-0x4(%rbp)
    176b:	89 75 f8             	mov    %esi,-0x8(%rbp)
    176e:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    1772:	75 3b                	jne    17af <_Z41__static_initialization_and_destruction_0ii+0x53>
    1774:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    177b:	75 32                	jne    17af <_Z41__static_initialization_and_destruction_0ii+0x53>
    177d:	48 8d 05 ce 29 00 00 	lea    0x29ce(%rip),%rax        # 4152 <_ZStL8__ioinit>
    1784:	48 89 c7             	mov    %rax,%rdi
    1787:	e8 34 fa ff ff       	call   11c0 <_ZNSt8ios_base4InitC1Ev@plt>
    178c:	48 8d 05 75 28 00 00 	lea    0x2875(%rip),%rax        # 4008 <__dso_handle>
    1793:	48 89 c2             	mov    %rax,%rdx
    1796:	48 8d 05 b5 29 00 00 	lea    0x29b5(%rip),%rax        # 4152 <_ZStL8__ioinit>
    179d:	48 89 c6             	mov    %rax,%rsi
    17a0:	48 8b 05 49 28 00 00 	mov    0x2849(%rip),%rax        # 3ff0 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    17a7:	48 89 c7             	mov    %rax,%rdi
    17aa:	e8 c1 f9 ff ff       	call   1170 <__cxa_atexit@plt>
    17af:	90                   	nop
    17b0:	c9                   	leave  
    17b1:	c3                   	ret    

00000000000017b2 <_GLOBAL__sub_I_queue.cpp>:
    17b2:	f3 0f 1e fa          	endbr64 
    17b6:	55                   	push   %rbp
    17b7:	48 89 e5             	mov    %rsp,%rbp
    17ba:	be ff ff 00 00       	mov    $0xffff,%esi
    17bf:	bf 01 00 00 00       	mov    $0x1,%edi
    17c4:	e8 93 ff ff ff       	call   175c <_Z41__static_initialization_and_destruction_0ii>
    17c9:	5d                   	pop    %rbp
    17ca:	c3                   	ret    

Disassembly of section .fini:

00000000000017cc <_fini>:
    17cc:	f3 0f 1e fa          	endbr64 
    17d0:	48 83 ec 08          	sub    $0x8,%rsp
    17d4:	48 83 c4 08          	add    $0x8,%rsp
    17d8:	c3                   	ret    
