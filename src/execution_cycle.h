#ifndef EXECUTION_CYCLE_H
#define EXECUTION_CYCLE_H

void halt (int32_t *args, struct machine_state *mach);

void fetch(int32_t pc, struct pipeline *pipeline, struct machine_state mach);

void decode(int32_t *instr, struct pipeline *pipeline, struct machine_state *mach);

bool equal(struct machine_state mach);

bool not_equal(struct machine_state mach);

bool greater_equal(struct machine_state mach);

bool less(struct machine_state mach);

bool greater(struct machine_state mach);

bool less_equal(struct machine_state mach);

bool always(struct machine_state mach);

bool condition(int cond_code, struct machine_state mach);



#endif