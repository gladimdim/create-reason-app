/* State might be empty or might have converted from JSON into Reason record of type Data.tResponse */
type state = {
    response: option(Data.tResponse)
};

/* SetResponse is used to update state */
/* LoadReports is used to call Fetch API via bs-fetch library */
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
            /* We use SideEffects as we cannot update state at this function stack call.
                It will be updated in when Fetch Promise is resolved with some data
            */
            | LoadReports => ReasonReact.SideEffects(
                (
                    self => Fetch.fetch(
                        "/data.json"
                    )
                    |> Js.Promise.then_(Fetch.Response.json)
                    |> Js.Promise.then_(json => {
                        /* json is completely unknown object for ReasonML type system */
                        /* so we have to decode it into ReasonML Record and then call another action to update component state */
                        /* This could be written in JavaScript style, but it is unreadable:
                            self.send(SetResponse(Data.decodeResponse(json)))
                        */
                        /* Notice how we create action by using lambda function
                            r => SetResponse(r)
                        */
                        json |> Data.decodeResponse |> r => SetResponse(r) |> self.send;
                        Js.Promise.resolve([]); /* we must satisfy compiler with some dummy return type */
                    })
                    |> ignore /* and here we ignore our resolved empty list */
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