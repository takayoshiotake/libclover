#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


typedef struct {
    int param;
    int stopped;
    int status;
    time_t timeout;
} a_task_context_t;


int progress_a_task(a_task_context_t * ctx) {
    while (!ctx->stopped) {
        switch(ctx->status) {
            case 0:
                printf("Task[0x%08x]: Hello\n", (unsigned int)ctx);

                ctx->status = 1;
                ctx->timeout = time(NULL) + 1;
                break;
            case 1:
                if (time(NULL) >= ctx->timeout) {
                    if (ctx->param > 0) {
                        printf("Task[0x%08x]: Continue\n", (unsigned int)ctx);
                        ctx->param -= 1;
                        ctx->timeout += 1;
                    } else {
                        printf("Task[0x%08x]: Bye\n", (unsigned int)ctx);
                        ctx->status = 2;
                    }
                } else {
                    return __LINE__;
                }
                break;
            case 2:
                ctx->stopped = 1;
                return 0;
        }
    }
    return -1;
}


int main(void) {
    a_task_context_t ctx1 = { 2, 0, 0, 0 };
    a_task_context_t ctx2 = { 5, 0, 0, 0 };

    // This is a task runner.
    for (;;) {
        progress_a_task(&ctx1);
        if (ctx1.stopped) {
            ctx2.stopped = 1;
        }
        progress_a_task(&ctx2);

        if (!ctx1.stopped || !ctx2.stopped) {
            sleep(1);
            continue;
        }
        break;
    }
    
    return 0;
}
