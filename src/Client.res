let headers = Js.Json.object_(Js.Dict.fromArray([("x-hasura-admin-secret", Js.Json.string("secret"))]))

/* Create an HTTP Link */
let httpLink = ApolloClient.Link.HttpLink.make(
  ~uri=_ => "http://localhost:8080/v1/graphql",
  ~headers=headers,
  (),
)

let instance = ApolloClient.make(~cache=ApolloClient.Cache.InMemoryCache.make(), ~link=httpLink, ())
