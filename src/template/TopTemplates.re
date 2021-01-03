[%graphql
  {|
    query GetTemplates {
      templates(order_by: [{score: desc}], limit: 10) {
          id
          name
          thumbnail_url
          preview_url
          score
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
    let frameStyle = ReactDOM.Style.make(~height="360px", ~width="640px", ());
    <div className=[%tw "container mx-auto text-center pt-10"]>
      <p className=[%tw "font-sans text-3xl mb-3"]>
        "Top 10 Templates"->React.string
      </p>
      <div className=[%tw "grid grid-cols-3 gap-5"]>
        {templates
         ->Belt.Array.map(t =>
             <div
               key={Js.String.make(t.id)}
               className=[%tw
                 "cursor-pointer flex flex-col items-center w-full"
               ]>
               <p className=[%tw "py-1"]> t.name->React.string </p>
               <img src={t.thumbnail_url} style=frameStyle />
             </div>
           )
         ->React.array}
      </div>
    </div>;
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};
