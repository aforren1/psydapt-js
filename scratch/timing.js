// using https://cdn.jsdelivr.net/npm/psydapt@0.0.3/dist/psydapt.min.js
createPsydapt().then(instance => { 
    let psydapt = instance; 
    
    x = new psydapt.Staircase({
        start_val: 0.5,
        n_reversals: 3,
        step_sizes: [0.01, 0.001], n_trials: 100,
        n_up: 4,
        n_down: 3,
        apply_initial_rule: true,
        stim_scale: "Linear",
        min_val: 0}
    )
    
    for (let i = 0; i < 100; i++) {
       let t0 = performance.now();
       x.next();
       let t1 = performance.now();
       x.update(i % 2);
       let t2 = performance.now();
       console.log('part1:', (t1 - t0), 'part2:', (t2 - t1));
    }
    
    console.log('Weibull');
    // next() take ~35ms on my firefox browser (i.e. 2 frames)
    // and in chromium it's ~10ms (!!)
    // in contrast, hoechenberger/questplus takes ~25ms
    y = new psydapt.QuestPlusWeibull({
        intensity: [-3.5, -3.25, -3, -2.75, -2.5, -2.25, -2, -1.75, -1.5, -1.25, -1, -0.75, -0.5],
        threshold: [-3.5, -3.25, -3, -2.75, -2.5, -2.25, -2, -1.75, -1.5, -1.25, -1, -0.75, -0.5],
        slope: [0.5, 4.125, 7.75, 11.375, 15],
        lower_asymptote: [0.01, 0.1325, 0.255, 0.3775, 0.5],
        lapse_rate: [0.01],
        stim_scale: 'Log10',
    })
    
    for (let i = 0; i < 100; i++) {
       let t0 = performance.now();
       y.next();
       let t1 = performance.now();
       y.update(i % 2);
       let t2 = performance.now();
       console.log('part1:', (t1 - t0), 'part2:', (t2 - t1));
    }
});
