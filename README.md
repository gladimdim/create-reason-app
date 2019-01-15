# create-reason-app
Contains skeleton app with such functionality: fetching REST resources via bs-fetch, parsing JSON via bs-json, reacting to user actions.

# Install
Clone this repo.

## Install Packages
```
yarn
```

# Run

You need to run these 3 tasks. They will watch for `ReasonML` changes, `Webpack` will rebuild the bundle and `serve` will serve files at http://localhost:3000
## Bucklescript watcher
```
npm run start
```
## Webpack watcher
```
npm run webpack
```
## Serve files
```
npm run deploy
```

# What is included

`bs-fetch` is used to work with REST calls.
`@glennsl/bs-json` is used to parse JSON from REST response into ReasonML real records
`Js.Promise` is used to work with async REST calls.
