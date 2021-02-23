JS Bindings to https://github.com/aforren1/psydapt.

Available on npm as an ES6 module: https://www.npmjs.com/package/psydapt

Or use a CDN: https://cdn.jsdelivr.net/npm/psydapt@0.1.3/dist/psydapt.min.js

To cut down on download sizes in production, single-routine files are also available. See https://cdn.jsdelivr.net/npm/psydapt@0.1.3/dist/

For now, see the C++ documentation for details: https://aforren1.github.io/psydapt/index.html

JSFiddle example: https://jsfiddle.net/su6jpxdq/

```js
import createPsydapt from 'psydapt.js'
let psydapt;
createPsydapt().then(instance => {

psydapt = instance;
x = new psydapt.staircase.Staircase({
    start_val: 0.5,
    n_reversals: 3,
    step_sizes: [0.01, 0.001],
    n_trials: 20,
    n_up: 4,
    n_down: 3,
    apply_initial_rule: true,
    stim_scale: psydapt.Scale.Linear,
    min_val: 0
})
let stim = x.next()
let finished = x.update(resp) // optional: x.update(resp, value)
...
x.delete()

let intensity = [-3.5, -3.25, -3, -2.75, -2.5,
                 -2.25, -2, -1.75, -1.5, -1.25,
                 -1, -0.75, -0.5]

// we also have QuestPlusNormCDF, with similar API
let qp = psydapt.questplus
y = new qp.Weibull({
    intensity: intensity,
    threshold: intensity,
    slope: [0.5, 4.125, 7.75, 11.375, 15],
    lower_asymptote: [0.01, 0.1325, 0.255, 0.3775, 0.5],
    lapse_rate: [0.01],
    stim_scale: psydapt.Scale.Linear
})

let stim = y.next()
let finished = y.update(resp) // optional: y.update(resp, value)
...
y.delete()

});

```
