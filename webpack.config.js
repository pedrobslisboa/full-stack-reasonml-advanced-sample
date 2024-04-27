const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyWebpackPlugin = require('copy-webpack-plugin');
const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

const Path = require("path");

let buildFolder = Path.join(
  __dirname,
  "_build/default/src/client/app/src/client"
);

module.exports = (env) => ({
  devtool: env.production ? false : "inline-cheap-module-source-map",
  entry: {
    app: Path.join(buildFolder, "/app.js"),
  },
  mode: env.production ? "production" : "development",
  output: {
    path: Path.join(__dirname, "public"),
    filename: "[name].js",
  },
  plugins: [
    (env.analize) ? new BundleAnalyzerPlugin({
      analyzerMode: 'static',
      reportFilename: 'analize.html',
    }) : null,
    new HtmlWebpackPlugin({
      filename: "index.html",
      template: "templates/index.html",
      publicPath: "/public",
    }),
    new CopyWebpackPlugin({
      patterns: [
          { from: 'assets'}
      ]
  })
  ],
});
