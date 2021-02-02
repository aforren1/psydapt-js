Make sure submodules-of-submodules are init (e.g. `git submodule update --init --recursive`)

Installed emsdk

./emsdk activate latest
source ./emsdk_env.sh

emcmake cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build && emmake make

Links:
https://emscripten.org/docs/compiling/Building-Projects.html

```js
import createPsydapt from 'psydapt.js'
let psydapt;
createPsydapt().then(instance => { psydapt = instance; });
x = new psydapt.Staircase({start_val: 0.5,
                           n_reversals: 3,
                           step_sizes: [0.01, 0.001], n_trials: 20,
                           n_up: 4,
                           n_down: 3,
                           apply_initial_rule: true,
                           stim_scale: "Linear",
                           min_val: 0})
...
x.delete()
```
