[@react.component]
let make = () => {
  <ApolloClient.React.ApolloProvider client=Client.instance>
    <Template/>
  </ApolloClient.React.ApolloProvider>;
};
