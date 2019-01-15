/*
    This is the main type of Item object in data.json file
*/
type t = {
    name: string,
    description: string,
    id: option(int)
};

/*
    This type corresponds to inner property 'data' in data.json.
    We use it to show how to process array of objects by using bs-json library.
*/

type tData = {
    data: array(t)
};

/*
    This is the root property in data.json.
    We use it to show, how to convert from JSON into Reason Records inner properties
*/
type tResponse = {
    response: tData
};

let decodeItem = (itemJson): t => {
    Json.Decode.{
        name: itemJson |> field("name", string),
        description: itemJson |> field("description", string),
        id: itemJson |> optional(field("id", int)) /* id field might be absend */
    }
};

let decodeData = (dJson) : tData => {
    Json.Decode.{
        data: dJson |> field("data", array(decodeItem))
        /* Here we take 'data' property and use Json.Decode.array method to process each
        element in JSON by mapping it to decodeItem function */
    }
}

/*
    Main function used to convert some JSON into valid Reason Records.
    The return value of this method is a strongly typed ReasonML record.
*/
let decodeResponse = (json) : tResponse => {
    Json.Decode.{
        response: json |> field("response", decodeData)
    }
}