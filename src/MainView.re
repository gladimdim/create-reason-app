type state = {
    response: option(Data.tResponse)
};

type action =
| SetResponse(Data.tResponse)
| LoadReports;

let component = ReasonReact.reducerComponent("MainView");

let make = (_children) => {
    ...component,
    initialState: () => {response: None},
    reducer: (action, _state) => 
        switch (action) {
            | SetResponse(reports) => ReasonReact.Update({response: Some(reports)})
            | LoadReports => ReasonReact.SideEffects(
                (
                    self => Fetch.fetch(
                        "/data.json"
                    )
                    |> Js.Promise.then_(Fetch.Response.json)
                    |> Js.Promise.then_(json => {
                        json |> Data.decodeResponse |> r => SetResponse(r) |> self.send;
                        Js.Promise.resolve([]);
                    })
                    |> ignore
                )
            )
    },
    render: self => {
        <div>
            <div>
                <button onClick={_event => self.send(LoadReports)}>
                    {ReasonReact.string("Load Reports")}
                </button>
            </div>
            {
                switch (self.state.response) {
                | Some(response) =>
                    <div>
                        {
                            Array.map(ItemView.renderItem, response.response.data)
                            |> ReasonReact.array
                        }
                    </div>
                | None => {ReasonReact.string("Data not fetched")}

                }
            }
        </div>
    }
};