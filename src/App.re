[@react.component]
let make = () => {
  <ApolloClient.React.ApolloProvider client=Client.instance>
    <div className=[%tw "container mx-auto text-center pt-10"]>
      <p className=[%tw "font-sans text-3xl mb-3"]>"Vote your favorite template"->React.string</p>
      <Template/>
    </div>
  </ApolloClient.React.ApolloProvider>;
};
