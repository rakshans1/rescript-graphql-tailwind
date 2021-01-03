[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  <ApolloClient.React.ApolloProvider client=Client.instance>
    <div className=[%tw "bg-gray-50 h-screen"]>
    {switch (url.path) {
     | ["admin"] => <TopTemplates />
     | _ => <Template />
     }}
  </div>
  </ApolloClient.React.ApolloProvider>;
};
