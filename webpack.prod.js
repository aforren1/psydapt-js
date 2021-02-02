const TerserPlugin = require("terser-webpack-plugin");
var path = require("path");

module.exports = {
  mode: "production",
  entry: path.resolve(__dirname) + "/index.js",
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: "psydapt.min.js",
  },
  module: {
    rules: [{ test: /\.js$/, exclude: /node_modules/, loader: "babel-loader" }],
  },
  optimization: {
    minimize: true,
    minimizer: [
      new TerserPlugin({
        terserOptions: {
          output: {
            comments: false,
          },
          warnings: false,
          parse: {},
          compress: {},
          output: null,
          toplevel: false,
          nameCache: null,
          ie8: false,
          keep_fnames: false,
        },
      }),
    ],
  },
};
