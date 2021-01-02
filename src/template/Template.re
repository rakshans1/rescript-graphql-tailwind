[%graphql
  {|
    query GetTemplates {
      templates(limit: 2) {
          id
          name
          thumbnail_url
          preview_url
      }
    }
  |}
];

[@react.component]
let make = () => {
  let queryResult = GetTemplates.use();
  switch (queryResult) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} => "Error loading data"->React.string
  | {data: Some({templates})} =>
    <div>
      <ul>
        {templates
         ->Belt.Array.map(t =>
             <li key={Js.String.make(t.id)}>
               <img src={t.thumbnail_url} />
               <p> t.name->React.string </p>
             </li>
           )
         ->React.array}
      </ul>
    </div>
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};
