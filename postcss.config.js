const purgecss = require("postcss-purgecss")({
  content: ["./src/**/*.re", "./src/**/*.res"],
  defaultExtractor: require("@dylanirlbeck/tailwind-ppx").extractor,
});

module.exports = {
  plugins: [
    require("tailwindcss"),
    require("autoprefixer"),
    ...(process.env.NODE_ENV === "production" ? [purgecss] : []),
  ],
};
