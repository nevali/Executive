# Talisker IDL parser

This is the back-end parser for Talisker IDL. It reads pre-processed IDL source supplied by the IDL compiler front-end, and emits JSON intermediate representation to standard-out.

The parser does not confirm the *validity* of the IDL: for example, that referenced types are properly defined; instead, core validation is performed by the front-end prior to invoking the desired generator back-end, and generator back-ends themselves may impose additional constraints (for example, because of differing underlying RPC capabilities).

The Talisker IDL grammar is a minor superset of Microsoft’s COM IDL syntax. Generally speaking, this parser should be able to deal with everything that `msidl` can.
