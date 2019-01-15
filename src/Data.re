type t = {
    name: string,
    description: string,
    id: option(int)
};

type tData = {
    data: array(t)
};

type tResponse = {
    response: tData
};

let decodeItem = (itemJson): t => {
    Json.Decode.{
        name: itemJson |> field("name", string),
        description: itemJson |> field("description", string),
        id: itemJson |> optional(field("id", int))
    }
};

let decodeData = (dJson) : tData => {
    Json.Decode.{
        data: dJson |> field("data", array(decodeItem))
    }
}

let decodeResponse = json => {
    Json.Decode.{
        response: json |> field("response", decodeData)
    }
}