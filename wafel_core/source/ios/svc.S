.section ".text"
.arm
.align 4

.extern semihosting_handler

.arm
.global svcCreateThread
.type svcCreateThread, %function
svcCreateThread:
	.word (0xE7F000F0 | 0x0 << 8)
	bx lr

.arm
.global svcJoinThread
.type svcJoinThread, %function
svcJoinThread:
	.word (0xE7F000F0 | 0x1 << 8)
	bx lr

.arm
.global svcCancelThread
.type svcCancelThread, %function
svcCancelThread:
	.word (0xE7F000F0 | 0x2 << 8)
	bx lr

.arm
.global svcGetThreadId
.type svcGetThreadId, %function
svcGetThreadId:
	.word (0xE7F000F0 | 0x3 << 8)
	bx lr

.arm
.global svcStartThread
.type svcStartThread, %function
svcStartThread:
	.word (0xE7F000F0 | 0x7 << 8)
	bx lr

.arm
.global svcSuspendThread
.type svcSuspendThread, %function
svcSuspendThread:
	.word (0xE7F000F0 | 0x8 << 8)
	bx lr

.arm
.global svcYieldThread
.type svcYieldThread, %function
svcYieldThread:
	.word (0xE7F000F0 | 0x9 << 8)
	bx lr

.arm
.global iosCreateMessageQueue
.type iosCreateMessageQueue, %function
iosCreateMessageQueue:
	.word (0xE7F000F0 | 0xC << 8)
	bx lr

.arm
.global iosDestroyMessageQueue
.type iosDestroyMessageQueue, %function
iosDestroyMessageQueue:
	.word (0xE7F000F0 | 0xD << 8)
	bx lr

.arm
.global iosSendMessage
.type iosSendMessage, %function
iosSendMessage:
	.word (0xE7F000F0 | 0xE << 8)
	bx lr

.arm
.global iosJamMessage
.type iosJamMessage, %function
iosJamMessage:
	.word (0xE7F000F0 | 0xF << 8)
	bx lr

.arm
.global iosReceiveMessage
.type iosReceiveMessage, %function
iosReceiveMessage:
	.word (0xE7F000F0 | 0x10 << 8)
	bx lr

.arm
.global iosCreateTimer
.type iosCreateTimer, %function
iosCreateTimer:
	.word (0xE7F000F0 | 0x13 << 8)
	bx lr

.arm
.global iosRestartTimer
.type iosRestartTimer, %function
iosRestartTimer:
	.word (0xE7F000F0 | 0x14 << 8)
	bx lr

.arm
.global iosStopTimer
.type iosStopTimer, %function
iosStopTimer:
	.word (0xE7F000F0 | 0x15 << 8)
	bx lr

.arm
.global iosDestroyTimer
.type iosDestroyTimer, %function
iosDestroyTimer:
	.word (0xE7F000F0 | 0x16 << 8)
	bx lr

.arm
.global svcAlloc
.type svcAlloc, %function
svcAlloc:
	.word (0xE7F000F0 | 0x27 << 8)
	bx lr

.arm
.global svcAllocAlign
.type svcAllocAlign, %function
svcAllocAlign:
	.word (0xE7F000F0 | 0x28 << 8)
	bx lr

.arm
.global svcFree
.type svcFree, %function
svcFree:
	.word (0xE7F000F0 | 0x29 << 8)
	bx lr

.arm
.global svcOpen
.type svcOpen, %function
svcOpen:
	.word (0xE7F000F0 | 0x33 << 8)
	bx lr

.arm
.global svcClose
.type svcClose, %function
svcClose:
	.word (0xE7F000F0 | 0x34 << 8)
	bx lr

.arm
.global svcIoctl
.type svcIoctl, %function
svcIoctl:
	.word (0xE7F000F0 | 0x38 << 8)
	bx lr

.arm
.global svcIoctlv
.type svcIoctlv, %function
svcIoctlv:
	.word (0xE7F000F0 | 0x39 << 8)
	bx lr

.arm
.global svcInvalidateDCache
.type svcInvalidateDCache, %function
svcInvalidateDCache:
	.word (0xE7F000F0 | 0x51 << 8)
	bx lr

.arm
.global svcFlushDCache
.type svcFlushDCache, %function
svcFlushDCache:
	.word (0xE7F000F0 | 0x52 << 8)
	bx lr

.arm
.global iosCreateSemaphore
.type iosCreateSemaphore, %function
iosCreateSemaphore:
	.word (0xE7F000F0 | 0x57 << 8)
	bx lr

.arm
.global iosWaitSemaphore
.type iosWaitSemaphore, %function
iosWaitSemaphore:
	.word (0xE7F000F0 | 0x58 << 8)
	bx lr

.arm
.global iosSignalSemaphore
.type iosSignalSemaphore, %function
iosSignalSemaphore:
	.word (0xE7F000F0 | 0x59 << 8)
	bx lr

.arm
.global iosDestroySemaphore
.type iosDestroySemaphore, %function
iosDestroySemaphore:
	.word (0xE7F000F0 | 0x5A << 8)
	bx lr

.arm
.global svcFlushIPCServer
.type svcFlushIPCServer, %function
svcFlushIPCServer:
	.word (0xE7F000F0 | 0x5B << 8)
	bx lr

.arm
.global iosPanic
.type iosPanic, %function
iosPanic:
	.word (0xE7F000F0 | 0x73 << 8)
	bx lr

.arm
.global iosLoadPpcKernel
.type iosLoadPpcKernel, %function
iosLoadPpcKernel:
	.word (0xE7F000F0 | 0x77 << 8)
	bx lr

.arm
.global svcBackdoor
.type svcBackdoor, %function
svcBackdoor:
	.word (0xE7F000F0 | 0x81 << 8)
	bx lr

.arm
.global svc_sys_write
.global svc_sys_write_arm
.type svc_sys_write_arm, %function
svc_sys_write_arm:
	adr r12, svc_sys_write+1
	bx r12

.pool

.thumb_func
.thumb
.type svc_sys_write, %function
svc_sys_write:
	mov r2, lr
	mov r1, r0
	mov r0, #4
	svc 0xAB
	bx r2

.arm
.global crash_and_burn
.type crash_and_burn, %function
crash_and_burn:
	.word 0xFFFFFFFF

.arm
.global svc_handler_hook
.type svc_handler_hook, %function
svc_handler_hook:
	push {r0-r12, lr}
	ldrh r0, [lr, #-2]
	ldr r1, =0xDFAB
	cmp r0, r1
	beq do_svc
	pop {r0-r12, lr}

	ldr pc, old_svc_handler
do_svc:
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	bl semihosting_handler
	.word 0xE8FD9FFF @ pop {r0-r12, pc}^

.align 4
.global old_svc_handler
old_svc_handler:
	.word 0x0