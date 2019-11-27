const core = require("@actions/core");
const exec = require("@actions/exec");
const request = require("request");
const fs = require("fs");

try {

  const name = core.getInput("name");
  const token = core.getInput("token");
  const flags = core.getInput("flags");
  const path = core.getInput("path");
  const yml = core.getInput("yml");

  request("https://codecov.io/bash", (error, response, body) => {
    if (error) throw error;

    fs.writeFile("codecov.sh", body, err => {
      if (err) throw err;

      let output = "";
      let execError = "";
      const options = {};
      options.listeners = {
        stdout: data => {
          output += data.toString();
        },
        stderr: data => {
          execError += data.toString();
        }
      };

      options.env = {
        CODECOV_TOKEN: `${token}`,
        GITHUB_ACTION: process.env.GITHUB_ACTION,
        GITHUB_REF: process.env.GITHUB_REF,
        GITHUB_REPOSITORY: process.env.GITHUB_REPOSITORY,
        GITHUB_SHA: process.env.GITHUB_SHA
      };

      exec
        .exec(
          "bash",
          ["codecov.sh", "-s", `${path}`, "-n", `${name}`, "-F", `${flags}`, '-y', `${yml}`],
          options
        )
        .then(() => {
          unlinkFile()
        });

      const unlinkFile = () => {
        fs.unlink("codecov.sh", err => {
          if (err) throw err;
        });
      }

    });
  });
} catch (error) {
  core.setFailed(error.message);
}
