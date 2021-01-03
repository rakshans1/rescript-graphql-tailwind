[%graphql
  {|
    query GetTemplates($offset: Int) {
      templates(limit: 2, offset: $offset) {
          id
          name
          thumbnail_url
          preview_url
          score
      }
    }
  |}
];

[%graphql
  {|
    mutation UpdateTemplateScore($id: Int, $score: Int) {
      update_templates(where: {id: { _eq: $id }}, _set: {score: $score}) {
        affected_rows
      }
    }
  |}
];

[@react.component]
let make = () => {
  let (offset, setOffset) = React.useState(_ => 0);
  let queryResult = GetTemplates.use({offset: Some(offset)});
  let (mutate, _) = UpdateTemplateScore.use();
  let refresh = () => {
    setOffset(prevOffset =>
      switch (prevOffset) {
      | 0 => 3
      | _ => prevOffset + 2
      }
    );
  };

  switch (queryResult) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} => "Error loading data"->React.string
  | {data: Some({templates})} =>
    let frameStyle = ReactDOM.Style.make(~height="360px", ~width="640px", ());
    <div className=[%tw "container mx-auto text-center pt-10"]>
      <p className=[%tw "font-sans text-3xl mb-3"]>
        "Vote your favorite template"->React.string
      </p>
      <div className=[%tw "flex"]>
        {templates
         ->Belt.Array.map(t =>
             <div
               key={Js.String.make(t.id)}
               className=[%tw
                 "px-2 text-center cursor-pointer flex flex-col items-center w-full"
               ]>
               /* <img src={t.thumbnail_url}  style=frameStyle/> */

                 <video
                   src={t.preview_url}
                   style=frameStyle
                   muted=true
                   autoPlay=true
                 />
                 <p className=[%tw "py-9"]> t.name->React.string </p>
                 <button
                   className=[%tw "px-5 py-2 bg-indigo-600 text-white"]
                   onClick={_ => {
                     mutate({id: Some(t.id), score: Some(t.score + 1)})
                     ->ignore;
                     refresh();
                   }}>
                   {React.string("Vote")}
                 </button>
               </div>
           )
         ->React.array}
      </div>
      <button
        className=[%tw "px-5 py-2 bg-gray-400 text-white"]
        onClick={_ => refresh()}>
        {React.string("Skip")}
      </button>
    </div>;
  | {data: None, error: None, loading: false} =>
    "I hope this is impossible, but sometimes it's not!"->React.string
  };
};
