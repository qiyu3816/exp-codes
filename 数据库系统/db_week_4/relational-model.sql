create domain BookISBN as VARCHAR(13);

create domain AuthorId as int;

create domain PublisherId as int;

create domain CategoryId as int;

create domain AddressId as int;

create domain PromotionId as int;

create domain OrderId as int;

create domain CustomerId as int;

create domain CardNum as VARCHAR(20);

create domain TrackingNumber as VARCHAR(20);

create table Address(
    address_id      int         NOT NULL UNIQUE,
    address_country VARCHAR(20) NOT NULL,
    address_state   VARCHAR(20) NOT NULL,
    address_city    VARCHAR(20) NOT NULL,
    address_street  VARCHAR(20) NOT NULL,
    PRIMARY KEY(address_id)
);

create table Author(
    author_id       int         NOT NULL UNIQUE,
    first_name      VARCHAR(10) NOT NULL,
    middle_name     VARCHAR(10) NOT NULL,
    last_name       VARCHAR(10) NOT NULL,
    address_id      AddressId   NOT NULL,
    email_address   VARCHAR(20) NOT NULL,
    PRIMARY KEY(author_id),
    FOREIGN KEY(address_id) references Address(address_id)
);

create table Publisher(
    publisher_id    int         NOT NULL UNIQUE,
    publisher_name  VARCHAR(20) NOT NULL,
    address_id      AddressId   NOT NULL,
    PRIMARY KEY(publisher_id),
    FOREIGN KEY(address_id) references Address(address_id)
);

create table Book(
    bISBN           VARCHAR(13)  NOT NULL UNIQUE,
    author_id       AuthorId     NOT NULL,
    bTitle          VARCHAR(20)  NOT NULL,
    publisher_id    PublisherId  NOT NULL,
    bVersion        int          NOT NULL,
    bPubDate        date         NOT NULL,
    bPrice          FLOAT(2)     NOT NULL,
    bDescription    VARCHAR(100),
    PRIMARY KEY(bISBN),
    FOREIGN KEY(author_id) references Author(author_id),
    FOREIGN KEY(publisher_id) references Publisher(publisher_id)
);

create table Book_Author(
    bISBN       BookISBN    NOT NULL,
    author_id   AuthorId    NOT NULL,
    PRIMARY KEY(bISBN, author_id),
    FOREIGN KEY(bISBN, author_id)
);

create table Category(
    category_id     int          NOT NULL UNIQUE,
    category_name   VARCHAR(20)  NOT NULL,
    PRIMARY KEY(category_id)
);

create table Book_Category(
    bISBN       BookISBN     NOT NULL,
    category_id CategoryId   NOT NULL,
    PRIMARY KEY(bISBN, category_id),
    FOREIGN KEY(bISBN) references Book(bISBN),
    FOREIGN KEY(category_id) references Category(category_id)
);

create table Promotion(
    promotion_id       int     NOT NULL UNIQUE,
    promotion_percent  int     NOT NULL,
    promotion_start    date    NOT NULL,
    promotion_end      date    NOT NULL,
    PRIMARY KEY(promotion_id)
);

create table Book_Promotion(
    bISBN        BookISBN     NOT NULL,
    promotion_id PromotionId  NOT NULL,
    PRIMARY KEY(bISBN, promotion_id),
    FOREIGN KEY(bISBN) references Book(bISBN),
    FOREIGN KEY(promotion_id) references Promotion(promotion_id)
);

create table CreditCard(
    card_number     VARCHAR(20)  NOT NULL UNIQUE,
    exp_date        date         NOT NULL,
    PRIMARY KEY(card_number)
);

create table Customer(
    customer_id     int         NOT NULL UNIQUE,
    card_number     CardNum     NOT NULL,
    first_name      VARCHAR(10) NOT NULL,
    middle_name     VARCHAR(10) NOT NULL,
    last_name       VARCHAR(10) NOT NULL,
    address_id      AddressId   NOT NULL,
    email_address   VARCHAR(20) NOT NULL,
    PRIMARY KEY(customer_id),
    FOREIGN KEY(address_id) references Address(address_id),
    FOREIGN KEY(card_number) references CreditCard(card_number)
);

create table SingleOrder(
    order_id    int        NOT NULL UNIQUE,
    customer_id CustomerId NOT NULL,
    address_id  AddressId  NOT NULL,
    card_number CardNum    NOT NULL,
    create_date date       NOT NULL,
    total_price float(2)   NOT NULL,
    PRIMARY KEY(order_id),
    FOREIGN KEY(customer_id) references Customer(customer_id),
    FOREIGN KEY(address_id) references Address(address_id),
    FOREIGN KEY(card_number) references CreditCard(card_number)
);

create table LineItem(
    order_id    OrderId     NOT NULL,
    bISBN       BookISBN    NOT NULL,
    quantity    int         NOT NULL default 1,
    total_price float(2)    NOT NULL,
    PRIMARY KEY(order_id, bISBN),
    FOREIGN KEY(bISBN) references Book(bISBN),
    FOREIGN KEY(order_id) references SingleOrder(order_id)
);

create table Shipment(
    tracking_num      VARCHAR(20)  NOT NULL UNIQUE,
    ship_date         date         NOT NULL,
    delivery_exp_date date         NOT NULL,
    PRIMARY KEY(tracking_num)
);

create table LineItem_Shipment(
    order_id     OrderId        NOT NULL,
    bISBN        BookISBN       NOT NULL,
    tracking_num TrackingNumber NOT NULL,
    PRIMARY KEY(order_id, bISBN, tracking_num),
    FOREIGN KEY(order_id) references SingleOrder(order_id),
    FOREIGN KEY(bISBN) references Book(bISBN),
    FOREIGN KEY(tracking_num) references Shipment(tracking_num)
);
