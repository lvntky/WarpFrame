=================================================================
==3020==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 20131200 byte(s) in 699 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x0000004315bd in wf_tile_create_grid src/wf_tile_manager.c:18
    #2 0x0000004042d6 in c_rasterizer_draw_triangle_solid src/c_rasterizer.c:274
    #3 0x00000040bb4e in main src/main.c:364
    #4 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #6 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Direct leak of 48 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000412a8f in wf_obj_normalize src/wf_obj_parser.c:121
    #2 0x00000040b477 in main src/main.c:320
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Direct leak of 48 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000411ab5 in wf_obj_parse src/wf_obj_parser.c:65
    #2 0x00000040b218 in main src/main.c:292
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Direct leak of 32 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000404a35 in c_renderer_init src/c_renderer.c:10
    #2 0x00000040b42c in main src/main.c:316
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x00000043085c in wf_texture_create_checkerboard src/wf_texture.c:19
    #2 0x00000040b2a4 in main src/main.c:298
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 307200 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae68c3 in calloc (/lib64/libasan.so.8+0xe68c3) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000404b08 in c_renderer_init src/c_renderer.c:15
    #2 0x00000040b42c in main src/main.c:316
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 307200 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae68c3 in calloc (/lib64/libasan.so.8+0xe68c3) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000404b94 in c_renderer_init src/c_renderer.c:16
    #2 0x00000040b42c in main src/main.c:316
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 307200 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000404c43 in c_renderer_init src/c_renderer.c:17
    #2 0x00000040b42c in main src/main.c:316
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 16384 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000430957 in wf_texture_create_checkerboard src/wf_texture.c:22
    #2 0x00000040b2a4 in main src/main.c:298
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 48 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000411ad0 in wf_obj_parse src/wf_obj_parser.c:66
    #2 0x00000040b218 in main src/main.c:292
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000411b10 in wf_obj_parse src/wf_obj_parser.c:68
    #2 0x00000040b218 in main src/main.c:292
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

Indirect leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x7f41f7ae6f4b in malloc (/lib64/libasan.so.8+0xe6f4b) (BuildId: d7d37a712ed67f505b486de13595e3f6cc124ee8)
    #1 0x000000411af5 in wf_obj_parse src/wf_obj_parser.c:67
    #2 0x00000040b218 in main src/main.c:292
    #3 0x7f41f70105b4 in __libc_start_call_main (/lib64/libc.so.6+0x35b4) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #4 0x7f41f7010667 in __libc_start_main@@GLIBC_2.34 (/lib64/libc.so.6+0x3667) (BuildId: 88c03969b4319fc0140734fe863825ec4a1cdb0d)
    #5 0x0000004009f4 in _start (/home/levent/Dev/WarpFrame/warpframe+0x4009f4) (BuildId: 7668ca3de6ca7b5727710fc75808bd804ff34231)

SUMMARY: AddressSanitizer: 21069424 byte(s) leaked in 710 allocation(s).
make: *** [Makefile:60: run-asan] Aborted
~/Dev/WarpFrame master !2 ❯                    
