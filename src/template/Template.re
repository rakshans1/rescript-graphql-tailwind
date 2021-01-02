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
    <div className=[%tw "flex"]>
        {templates
         ->Belt.Array.map(t =>
             <div key={Js.String.make(t.id)} className=[%tw "px-2 text-center cursor-pointer"]>
               /* <img src={t.thumbnail_url} /> */
               <video src={t.preview_url}  controls=true/>
               <p> t.name->React.string </p>
             </div>
           )
         ->React.array}
    </div>
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};
