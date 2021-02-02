var path = require("path");

module.exports = {
  mode: "production",
  entry: path.resolve(__dirname) + "/build/psydapt.js",
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: "psydapt.min.js",
    library: "createPsydapt",
    libraryTarget: "umd",
    libraryExport: "default",
  },
  module: {
    rules: [{ test: /\.js$/, exclude: /node_modules/, loader: "babel-loader" }],
  },
};
