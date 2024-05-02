var jsonStringify = function(obj) {
    if (obj === null) {
        return 'null';
    }

    if (obj instanceof Array) {
        const elements = obj.map(jsonStringify);
        return `[${elements.join(',')}]`;
    }

    if (obj instanceof Object) {
        const keys = Object.keys(obj);
        const elements = keys.map(key => `"${key}":${jsonStringify(obj[key])}`);
        return `{${elements.join(',')}}`;
    }

    if (typeof obj === 'string') {
        return `"${obj}"`;
    }

    return obj.toString();
};

console.log(jsonStringify({"y":1,"x":2}));
console.log(jsonStringify(0));
console.log(jsonStringify({"a":"str","b":-12,"c":true,"d":null}));
console.log(jsonStringify({"key":{"a":1,"b":[{},null,"Hello"]}}));
console.log(jsonStringify(true));
console.log(jsonStringify("kaushal agrawal"));

