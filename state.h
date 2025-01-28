#ifndef AUDIOOP_STATE_H
#define AUDIOOP_STATE_H

typedef struct _audioop_state {
    PyObject *AudioopError;
} audioop_state;

static inline audioop_state *
get_audioop_state(PyObject *module)
{
    void *state = PyModule_GetState(module);
    assert(state != NULL);
    return (audioop_state *)state;
}

#endif // AUDIOOP_STATE_H
