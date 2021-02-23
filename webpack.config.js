var path = require("path");

module.exports = (env) => {
  let input = env.input;
  console.log(`File: ${input}`);
  let base_out = input.substring(0, input.indexOf("-es6.js"));
  return {
    mode: "production",
    context: path.resolve(__dirname, "dist"),
    entry: `./${input}`,
    output: {
      path: path.resolve(__dirname, "dist"),
      filename: `${base_out}.min.js`,
      library: "createPsydapt",
      libraryTarget: "umd",
      libraryExport: "default",
    },
    module: {
      rules: [
        { test: /\.js$/, exclude: /node_modules/, loader: "babel-loader" },
      ],
    },
  };
};
